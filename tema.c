/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tema.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxencefournier <maxencefournier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:29:37 by maxencefour       #+#    #+#             */
/*   Updated: 2025/02/08 18:01:17 by maxencefour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <iso646.h>

typedef enum e_operator_kind {
        kind_none        = 0,
        kind_redir_left  = 1,
        kind_redir_right = 2,
        kind_pipe        = 3,
}t_operator_kind;


/*

[echo]     kind_identifier
[$VAR]     kind_variable
[>>file]   kind_unknown
[|]        kind_pipe
[cat]      kind_identifier
[|rev]     kind_unknown
[>intfile] kind_unknown

*/


bool is_valid_redir_left(char *string, size_t remaining) {
        size_t i                = 1;
        size_t redir_left_count = 1;

        while (i < remaining && string[i] == '<') 
        {
            redir_left_count += 1;
            ++i;
        }
        return (redir_left_count <= 2);
}

bool is_valid_redir_right(char *string, size_t remaining) 
{
        size_t i                = 1;
        size_t redir_left_count = 1;

        while (i < remaining && string[i] == '>') 
        {
                redir_left_count += 1;
                ++i;
        }

        return (redir_left_count <= 2);
}

bool is_valid_pipe(char *string, size_t remaining) {
        size_t i                = 1;
        size_t redir_left_count = 1;

        if (string[i] == '\0') 
        {
                return false;
        }

        while (i < remaining && string[i] == '|') 
        {
                redir_left_count += 1;
                ++i;
        }

        return (redir_left_count <= 1);
}

bool is_valid_operator(char *string, size_t remaining, t_operator_kind kind) {
        if (kind == kind_pipe) {
                return is_valid_pipe(string, remaining);
        } else if (kind == kind_redir_right) {
                return is_valid_redir_right(string, remaining);

        } else if (kind == kind_redir_left) {
                return is_valid_redir_left(string, remaining);
        }
        return true;
}


bool is_operator(char ch, t_operator_kind *out_kind) 
{
        if (ch == '|')
        {
                *out_kind = kind_pipe;
                return true;
        } else if (ch == '>') 
        {
                *out_kind = kind_redir_right;
                return true;
        } else if (ch == '<') 
        {
                *out_kind = kind_redir_left;
                return true;
        }
        return false;
}

bool check_syntax(char *string, size_t len) 
{
        size_t          i          = 0;
        t_operator_kind maybe_kind = kind_none;

        while (i < len) 
        {

                if (is_operator(string[i], &maybe_kind))
                {
                        if (is_valid_operator(&string[i], len - i, maybe_kind)) 
                        {
                                // printf("%s\n", &string[i]);
                        } 
                        else 
                        {
                                printf("syntax error at '%s'\n", &string[i]);
                                return false;
                        }
                }
                ++i;
        }
        return true;
}

int main(int argc, char **argv) {

        int i = 1;

        while (i < argc) {
                size_t len = strlen(argv[i]);
                printf("%s\n", check_syntax(argv[i], len) == true ? "True" : "False");
                printf("%s\n", argv[i]);
                i++;
        }
        return (0);
}