#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_COLUMN_NAME 50
#define MAX_ROWS 100
#define MAX_TABLES 10
#define MAX_ROW_SIZE 100
#define BPLUS_TREE_ORDER 5

// �ж���
typedef struct {
    char name[MAX_COLUMN_NAME];
    int type; // 0 for int, 1 for string
} Column;

// B+���ڵ㶨��
typedef struct BPlusTreeNode {
    int keyCount;
    int keys[BPLUS_TREE_ORDER - 1];
    struct BPlusTreeNode* children[BPLUS_TREE_ORDER];
} BPlusTreeNode;

// ����
typedef struct Table {
    char name[MAX_COLUMN_NAME];
    int column_count;
    Column columns[MAX_COLUMN_NAME];
    int row_count;
    char data[MAX_ROWS][MAX_ROW_SIZE];
    BPlusTreeNode* bplusTree; // B+������
} Table;

Table tables[MAX_TABLES];
int table_count = 0;

// ����B+���ڵ�
BPlusTreeNode* createBPlusTreeNode() {
    BPlusTreeNode* node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    node->keyCount = 0;
    for (int i = 0; i < BPLUS_TREE_ORDER; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// �������B+���ڵ�
void insertKey(BPlusTreeNode* node, int key) {
    int i = node->keyCount - 1;
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i + 1] = node->keys[i];
        i--;
    }
    node->keys[i + 1] = key;
    node->keyCount++;
}

// ����B+���ڵ�
BPlusTreeNode* splitNode(BPlusTreeNode* node) {
    BPlusTreeNode* newNode = createBPlusTreeNode();
    newNode->keyCount = BPLUS_TREE_ORDER / 2 - 1;
    for (int i = 0; i < newNode->keyCount; i++) {
        newNode->keys[i] = node->keys[BPLUS_TREE_ORDER / 2 + i];
    }
    for (int i = 0; i < BPLUS_TREE_ORDER / 2; i++) {
        newNode->children[i] = node->children[BPLUS_TREE_ORDER / 2 + i];
    }
    node->keyCount = BPLUS_TREE_ORDER / 2 - 1;
    return newNode;
}

// �������ݵ�B+��
BPlusTreeNode* insertBPlusTree(BPlusTreeNode* node, int key) {
    if (node == NULL) {
        node = createBPlusTreeNode();
        insertKey(node, key);
        return node;
    }
    if (node->keyCount < BPLUS_TREE_ORDER - 1) {
        insertKey(node, key);
        return node;
    }
    BPlusTreeNode* newNode = splitNode(node);
    int midKey = newNode->keys[0];
    if (key < midKey) {
        insertKey(node, midKey);
        node->children[BPLUS_TREE_ORDER / 2] = newNode;
    } else {
        insertKey(newNode, midKey);
        newNode->children[BPLUS_TREE_ORDER / 2] = node;
        node = newNode;
    }
    return node;
}

// ������
int create_table(const char* name, int column_count, Column* columns) {
    if (table_count >= MAX_TABLES) {
        return -1;
    }
    Table* table = &tables[table_count];
    strncpy(table->name, name, MAX_COLUMN_NAME - 1);
    table->name[MAX_COLUMN_NAME - 1] = '\0';
    table->column_count = column_count;
    for (int i = 0; i < column_count; i++) {
        strncpy(table->columns[i].name, columns[i].name, MAX_COLUMN_NAME - 1);
        table->columns[i].name[MAX_COLUMN_NAME - 1] = '\0';
        table->columns[i].type = columns[i].type;
    }
    table->row_count = 0;
    table->bplusTree = NULL; // ��ʼ�� B+������Ϊ NULL
    table_count++;
    return 0;
}

// ��������
int insert(Table* table, char* data) {
    if (table->row_count >= MAX_ROWS) {
        return -1;
    }
    strncpy(table->data[table->row_count], data, MAX_ROW_SIZE - 1);
    table->data[table->row_count][MAX_ROW_SIZE - 1] = '\0';
    // �������ݵĵ�һ���ֶ���������������Ϊ����
    char* token = strtok(data, ",");
    int key = atoi(token);
    table->bplusTree = insertBPlusTree(table->bplusTree, key);
    table->row_count++;
    return 0;
}

// ɾ������
int deleteRow(Table* table, int row_index) {
    if (row_index < 0 || row_index >= table->row_count) {
        return -1;
    }
    for (int i = row_index; i < table->row_count - 1; i++) {
        strncpy(table->data[i], table->data[i + 1], MAX_ROW_SIZE - 1);
        table->data[i][MAX_ROW_SIZE - 1] = '\0';
    }
    table->row_count--;
    return 0;
}

// ��������
int update(Table* table, int row_index, char* new_data) {
    if (row_index < 0 || row_index >= table->row_count) {
        return -1;
    }
    strncpy(table->data[row_index], new_data, MAX_ROW_SIZE - 1);
    table->data[row_index][MAX_ROW_SIZE - 1] = '\0';
    return 0;
}

// ��ѯ����
void select(Table* table) {
    // ��ӡ��ͷ
    printf("%-*s", MAX_COLUMN_NAME, "id");
    printf("%-*s\n", MAX_COLUMN_NAME, "name");

    // ��ӡ����
    for (int i = 0; i < table->row_count; i++) {
        char* row = table->data[i];
        char* id = strtok(row, ",");
        char* name = strtok(NULL, ",");
        printf("%-*s", MAX_COLUMN_NAME, id);
        printf("%-*s\n", MAX_COLUMN_NAME, name);
    }
}

// ����B+���еļ�
int searchBPlusTree(BPlusTreeNode* node, int key) {
    if (node == NULL) {
        return -1; // ��������
    }
    for (int i = 0; i < node->keyCount; i++) {
        if (node->keys[i] == key) {
            // �ҵ��������������ݵ�����
            return i; // ���������ݵ���������������е�λ����ͬ
        }
        if (node->keys[i] > key) {
            // ��С�ڵ�ǰ��������������
            if (node->children[i] != NULL) {
                int index = searchBPlusTree(node->children[i], key);
                if (index != -1) {
                    return index; // ���������ҵ���
                }
            }
            break;
        }
    }
    // ����������
    if (node->children[node->keyCount] != NULL) {
        return searchBPlusTree(node->children[node->keyCount], key);
    }
    return -1; // ��������
}

// ���ݼ���ѯ����
char* query(Table* table, int key) {
    int rowIndex = searchBPlusTree(table->bplusTree, key);
    if (rowIndex != -1) {
        return table->data[rowIndex]; // �����ҵ���������
    }
    return NULL; // δ�ҵ�����
}

int main() {
    Column columns[] = {
        {"id", 0},
        {"name", 1}
    };

    create_table("users", 2, columns);

    char data1[] = "1,John Doe";
    char data2[] = "2,Jane Doe";
    char data3[] = "3,Frau Anna";
    char data4[] = "4,Mr Max";
    
    insert(&tables[0], data1);
    insert(&tables[0], data2);
	insert(&tables[0], data3);
	insert(&tables[0], data4);

    select(&tables[0]);

    // ��ѯidΪ3������
    char* result = query(&tables[0], 3);
    if (result != NULL) {
        printf("Query result: %s\n", result);
    } else {
        printf("No data found for id 3.\n");
    }

    return 0;
}
