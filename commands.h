
/**
 * @authors Eduardo Oliveira; Alberto Simões;
 * @email eduardo.oliveira@ieee.org;
 * @create date 28-11-2019 19:59:00
 * @modify date 28-11-2019 19:59:00
 * @desc Command interpreter - SVG creator
 * @version 0.0.1
 */

typedef struct _value
{
    int val;
    char *var;
} Value;

Value *new_int_value(int v);
Value *new_var_value(char *v);

typedef struct _symbolTable
{
    char *var;
    float val;
    struct _symbolTable *next;
} SymbolTable;

typedef struct _turtle
{
    float x, y;
    float rot;
    SymbolTable *vars;
} Turtle;

Turtle *new_turtle();

typedef enum
{
    FORWARD,
    ROTATE_RIGHT,
    REPEAT,
    MK
} commandType;

typedef struct _command
{
    commandType type;             // Name of the command
    Value *arg1;                  // 1st argument
    Value *arg2;                  // 2nd argument
    struct _command *subCommands; // In case of repeat
    struct _command *next;        // Next command

} command;

command *insert_Make(command *lst, char *var_name, Value *var_value);
command *insert_Repeat(command *lst, Value *times, command *sc);
command *insert_Forward(command *lst, Value *dist);
command *insert_RotateRight(command *lst, Value *graus);
void DebugCommands(command *lst);
void Draw(command *lst);
