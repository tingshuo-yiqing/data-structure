# C语言字符串

### 字符串定义

```c
char *str1 = {"Hello world!"};  // 方式一 (可省略{})
char str2[] = {"Hello world!"}; // 方式二 (可省略{})
char str3[] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!', '\0'}; // 方式三
```


### 输入输出

所需头文件:`stdio.h`

**[getchar](https://www.cppreference.com/w/c/io/getchar.html)**
`int getchar( void );`

`getchar()` 一次只读 一个字符，类型是 int（不是 char）。
可以通过while循环实现读取一行
```c
int main() {
    char line[1000];
    int i = 0;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        // 当从文件读数据或用 Ctrl+Z（Windows）/Ctrl+D（Linux）时，getchar() 会返回 EOF。
        line[i++] = ch;
    }
    line[i] = '\0'; // 手动添加字符串结束符，否则 printf("%s", line) 打印时会读出垃圾字符。

    printf("你输入的是：%s\n", line);
    return 0;
}
```

**[fgets](https://www.cppreference.com/w/c/io/fgets.html)**
`char* fgets( char*  str, int count, FILE*  stream );`
`fgets()` 会自动在读到换行或 EOF 时停止，并保留换行符 `\n`（如果缓冲区够大）和自动补`\0`。所以一般要去掉那个多余的换行，不然会导致字符串的大小多1

```c
char line[256];
fgets(line, sizeof(line), stdin);
line[strcspn(line, "\n")] = 0; // 去掉换行符
printf("%s", line);
```

**[puts](https://www.cppreference.com/w/c/io/puts.html)**
`int puts( const char* str );`

用于输出一个以 `\0` 结尾的字符串，并在结尾自动输出一个换行符`\n`。如果没有`\0`会有未定义行为

### 遍历

```c
for (size_t i = 0; i < strlen(str2); ++i) {
    printf("%c ", str2[i]);
}
printf("\n");
// 使用指针遍历时，定义一个新指针遍历
for (const char* p = str1; *p; ++p) {
    printf("%c ", *p);
}
```
### 字符串函数


| 函数                    | 作用                                     | 示例                     |
| --------------------- | -------------------------------------- | ---------------------- |
| `int isalnum(int c)`  | 判断是否为字母或数字（A–Z, a–z, 0–9）              | `'A'`→真 `'%'`→假        |
| `int isalpha(int c)`  | 判断是否为字母                                | `'b'`→真 `'7'`→假        |
| `int isdigit(int c)`  | 判断是否为数字字符                              | `'5'`→真 `'x'`→假        |
| `int islower(int c)`  | 判断是否为小写字母                              | `'a'`→真 `'A'`→假        |
| `int isupper(int c)`  | 判断是否为大写字母                              | `'Z'`→真 `'z'`→假        |
| `int isspace(int c)`  | 判断是否为空白字符（空格、`\t`、`\n`、`\r`、`\v`、`\f`） | `' '`或`\n`→真           |
| `int tolower(int c)` | 转为小写字母 | `'A'`→`'a'` |
| `int toupper(int c)` | 转为大写字母 | `'a'`→`'A'` |

所需头文件:`string.h`和`ctype.h`，这些函数处理的字符串(数组)必须要以`'\0'`为终止符`null-terminated`

**[strcmp](https://en.cppreference.com/w/c/string/byte/strcmp.html)**
`int strcmp( const char* lhs, const char* rhs );`

比较两个字符串，返回`int`，常用来比较两个字符串是否相等(在C语言中判断相同不能直接==)

**[strcat](https://en.cppreference.com/w/c/string/byte/strcat.html)**
`char *strcat( char *dest, const char *src );`

将源串`src`拼接到目标字符串`dest`的`'\o'`后面，应确保`dest`足够大不然会溢出，拼接后`dest`自带一个`'\0'`
拷贝成功返回0，失败返回非0

**[strlen]()**
`size_t strlen( const char* str );`

返回字符串的长度，遍历到`'\0'`结束所以不包括`'\0'`，未开启 O2 优化时，该操作写在循环条件中复杂度是 O(𝑁)的。

**辨析**：sizeof 与 strlen
* sizeof 是 编译期运算，不会遍历字符串；
* strlen 是 运行期函数，会遍历直到遇到 '\0'；
* 当数组名传入函数（如 printf("%s")）时，它会自动衰变为指针。

**[strcpy](https://en.cppreference.com/w/c/string/byte/strcpy.html)**
`char* strcpy( char* dest, const char* src );`

将源串拷贝到`dest`指针，同样确保`dest`足够大。
拷贝成功返回0，失败返回非0

辨析：与`strdup`的区别

### 字符函数

所需头文件: `stdlib.h`

**[atoi](https://en.cppreference.com/w/c/string/byte/atoi.html)**
`int   atoi ( const char* str );`

* atoi -> int
* atol -> long
* atoll -> long long

遍历字符串将字符数转化为数字，可以转化负数，碰到一个非字符数字结束。如果转化成功返回对应数字，否则返回0

**[strtok](https://en.cppreference.com/w/c/string/byte/strtok)**
`char* strtok( char* str, const char* delim );`

将字符串按指定的分隔符分割成多个子字符串（标记）`delim`替换成`\0`，返回值是指向当前分割出的token（子串）的指针；没有更多 token 时返回 NULL。



```c
int main() {
    char input[] = "10 6 9 3 + -11 * / * 17 + 5 +";  // 带空格的字符串
	char* tokens[50001];
    int count = 0;

    // 用 strtok 分割字符串
    char* p = strtok(input, " ");
    while (p != NULL) {
        tokens[count++] = p;

        puts(tokens[count - 1]); 
        
        p = strtok(NULL, " "); // 内部要保存状态，所以传NULL而不是再传str
    }
	return 0;
}
```

### 字符串数组定义

```c
// 方式一：必须指定第二维的大小，且应大于等于数组最长字符串的长度
char str_arr1[][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}; 
// 方式二
char *str_arr2[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
```


