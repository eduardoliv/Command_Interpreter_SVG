#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include <math.h>

/**
 * @authors Eduardo Oliveira; Alberto Simões;
 * @email eduardo.oliveira@ieee.org;
 * @create date 28-11-2019 19:59:00
 * @modify date 28-11-2019 19:59:00
 * @desc Command interpreter - SVG creator
 * @version 0.0.1
 */

Value *new_int_value(int v)
{
    Value *val = (Value *)malloc(sizeof(Value));
    val->val = v;
    val->var = NULL;
    return val;
}
Value *new_var_value(char *v)
{
    Value *val = (Value *)malloc(sizeof(Value));
    val->var = v;
    return val;
}

Turtle *new_turtle()
{
    Turtle *turtle = (Turtle *)malloc(sizeof(Turtle));
    turtle->x = turtle->y = 200;
    turtle->rot = M_PI / 2;
    turtle->vars = NULL;
    return turtle;
}

float findVar(SymbolTable *vars, char *var)
{
    if (vars == NULL)
    {
        fprintf(stderr, "Variable %s undefined!\n", var);
        exit(1);
    }
    if (strcmp(vars->var, var) == 0)
    {
        return vars->val;
    }
    else
    {
        return findVar(vars->next, var);
    }
}

float evalVar(SymbolTable *vars, Value *value)
{
    // 1. Validate if value is INT or VAR
    if (value->var == NULL)
        return value->val;
    // 2. Obtain the var value
    return findVar(vars, value->var);
}

SymbolTable *updateVar(SymbolTable *vars, char *var, float val)
{
    if (vars == NULL)
    {
        SymbolTable *node = (SymbolTable *)malloc(sizeof(SymbolTable));
        node->next = NULL;
        node->var = strdup(var); // keep a fresh copy of the variable name
        node->val = val;
        return node;
    }
    else
    {
        if (strcmp(vars->var, var) == 0)
        {
            vars->val = val;
            return vars;
        }
        else
        {
            vars->next = updateVar(vars->next, var, val);
            return vars;
        }
    }
}

void DrawCommands(Turtle *turtle, command *lst)
{
    if (!lst)
        return;
    switch (lst->type)
    {
    case MK:
        // arg1 => name of the variable
        // arg2 => value of the variable
        {
            float varValue = evalVar(turtle->vars, lst->arg2);
            turtle->vars = updateVar(turtle->vars, lst->arg1->var, varValue);
        }
        break;
    case ROTATE_RIGHT:
        {
            float v = evalVar(turtle->vars, lst->arg1);
            float rad = 2 * M_PI * v / 360;
            turtle->rot -= rad;
        }
        break;
    case FORWARD:
    {
        float v = evalVar(turtle->vars, lst->arg1);
        float x2 = cos(turtle->rot) * v + turtle->x;
        float y2 = -sin(turtle->rot) * v + turtle->y;
        printf(
            "<line x1='%f' x2='%f' y1='%f' y2='%f' style='stroke:black;'/>\n",
            turtle->x, x2, turtle->y, y2);
        turtle->x = x2;
        turtle->y = y2;
    }
    break;
    case REPEAT:
    {
        float v = evalVar(turtle->vars, lst->arg1);
        for (int i = 0; i < v; i++)
        {
            DrawCommands(turtle, lst->subCommands);
        }
    }
    break;
    }
    DrawCommands(turtle, lst->next);
}

void Draw(command *lst)
{
    Turtle *turtle = new_turtle();
    printf("<?xml version=\"1.0\"?>\n");
    printf("<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
    DrawCommands(turtle, lst);
    printf("</svg>\n");
}

command *insert_Repeat(command *lst, Value *times, command *sc)
{
    command *node = (command *)malloc(sizeof(command));
    node->type = REPEAT;
    node->arg1 = times;
    node->subCommands = sc;
    node->next = lst;
    return node;
}

command *insert_Forward(command *lst, Value *dist)
{
    command *node = (command *)malloc(sizeof(command));
    node->type = FORWARD;
    node->arg1 = dist;
    node->subCommands = NULL;
    node->next = lst;
    return node;
}

command *insert_RotateRight(command *lst, Value *graus)
{
    command *node = (command *)malloc(sizeof(command));
    node->type = ROTATE_RIGHT;
    node->arg1 = graus;
    node->subCommands = NULL;
    node->next = lst;
    return node;
}

command *insert_Make(command *lst, char *var_name, Value *var_value)
{
    command *node = (command *)malloc(sizeof(command));
    node->type = MK;
    node->arg1 = new_var_value(var_name);
    node->arg2 = var_value;
    node->subCommands = NULL;
    node->next = lst;
    return node;
}