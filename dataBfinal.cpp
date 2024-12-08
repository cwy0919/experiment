#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_COLUMN_NAME 50
#define MAX_ROWS 100
#define MAX_TABLES 10
#define MAX_ROW_SIZE 100
#define BPLUS_TREE_ORDER 5

// 列定义
typedef struct {
    char name[MAX_COLUMN_NAME];
    int type; // 0 for int, 1 for string
} Column;

// B+树节点定义
typedef struct BPlusTreeNode {
    int keyCount;
    int keys[BPLUS_TREE_ORDER - 1];
    struct BPlusTreeNode* children[BPLUS_TREE_ORDER];
} BPlusTreeNode;

// 表定义
typedef struct Table {
    char name[MAX_COLUMN_NAME];
    int column_count;
    Column columns[MAX_COLUMN_NAME];
    int row_count;
    char data[MAX_ROWS][MAX_ROW_SIZE];
    BPlusTreeNode* bplusTree; // B+树索引
} Table;

Table tables[MAX_TABLES];
int table_count = 0;

// 创建B+树节点
BPlusTreeNode* createBPlusTreeNode() {
    BPlusTreeNode* node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    node->keyCount = 0;
    for (int i = 0; i < BPLUS_TREE_ORDER; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// 插入键到B+树节点
void insertKey(BPlusTreeNode* node, int key) {
    int i = node->keyCount - 1;
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i + 1] = node->keys[i];
        i--;
    }
    node->keys[i + 1] = key;
    node->keyCount++;
}

// 分裂B+树节点
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

// 插入数据到B+树
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

// 创建表
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
    table->bplusTree = NULL; // 初始化 B+树索引为 NULL
    table_count++;
    return 0;
}

// 插入数据
int insert(Table* table, char* data) {
    if (table->row_count >= MAX_ROWS) {
        return -1;
    }
    strncpy(table->data[table->row_count], data, MAX_ROW_SIZE - 1);
    table->data[table->row_count][MAX_ROW_SIZE - 1] = '\0';
    // 假设数据的第一个字段是整数，可以作为索引
    char* token = strtok(data, ",");
    int key = atoi(token);
    table->bplusTree = insertBPlusTree(table->bplusTree, key);
    table->row_count++;
    return 0;
}

// 删除数据
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

// 更新数据
int update(Table* table, int row_index, char* new_data) {
    if (row_index < 0 || row_index >= table->row_count) {
        return -1;
    }
    strncpy(table->data[row_index], new_data, MAX_ROW_SIZE - 1);
    table->data[row_index][MAX_ROW_SIZE - 1] = '\0';
    return 0;
}

// 查询数据
void select(Table* table) {
    // 打印表头
    printf("%-*s", MAX_COLUMN_NAME, "id");
    printf("%-*s\n", MAX_COLUMN_NAME, "name");

    // 打印数据
    for (int i = 0; i < table->row_count; i++) {
        char* row = table->data[i];
        char* id = strtok(row, ",");
        char* name = strtok(NULL, ",");
        printf("%-*s", MAX_COLUMN_NAME, id);
        printf("%-*s\n", MAX_COLUMN_NAME, name);
    }
}

// 搜索B+树中的键
int searchBPlusTree(BPlusTreeNode* node, int key) {
    if (node == NULL) {
        return -1; // 键不存在
    }
    for (int i = 0; i < node->keyCount; i++) {
        if (node->keys[i] == key) {
            // 找到键，返回行数据的索引
            return i; // 假设行数据的索引与键在数组中的位置相同
        }
        if (node->keys[i] > key) {
            // 键小于当前键，搜索左子树
            if (node->children[i] != NULL) {
                int index = searchBPlusTree(node->children[i], key);
                if (index != -1) {
                    return index; // 在子树中找到键
                }
            }
            break;
        }
    }
    // 搜索右子树
    if (node->children[node->keyCount] != NULL) {
        return searchBPlusTree(node->children[node->keyCount], key);
    }
    return -1; // 键不存在
}

// 根据键查询数据
char* query(Table* table, int key) {
    int rowIndex = searchBPlusTree(table->bplusTree, key);
    if (rowIndex != -1) {
        return table->data[rowIndex]; // 返回找到的数据行
    }
    return NULL; // 未找到数据
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

    // 查询id为3的数据
    char* result = query(&tables[0], 3);
    if (result != NULL) {
        printf("Query result: %s\n", result);
    } else {
        printf("No data found for id 3.\n");
    }

    return 0;
}
