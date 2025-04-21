#include "../include/minishell.h"

// t_token *lexer_get_word(t_lexer *lexer)
// {
//     char *word;
//     int i;

//     i = 0;
//     while (!is_special(lexer->line[lexer->i + i]))
//         i++;
//     word = ft_malloc((i + 1 ) * sizeof(char) );
//     if (!word)
//         return (NULL); // al marjo t freeyi w t exit in a clean
//     int j = 0;
//     while (j < i)
//     {
//         word[j] = lexer->c;
//         j++;
//         if (j < i)
//             lexer_advance(lexer);
//     }
//     word[j] = '\0';
//     return (init_token(word, WORD));
// }

t_token *lexer_get_word(t_lexer *lexer)
{
    char *word;
    int word_size;
    int i;

    word_size = get_word_size(lexer);
    word = ft_malloc((word_size + 1 ) * sizeof(char) );
    if (!word)
        return (NULL); // al marjo t freeyi w t exit in a clean
    i = 0;
    while (i < word_size)
    {
        word[i] = lexer->c;
        i++;
        if (i < word_size)
            lexer_advance(lexer);
    }
    word[i] = '\0';
    return (init_token(word, WORD));
}

// t_token *lexer_get_heredoc(t_lexer *lexer)
// {
//     char *herdoc;
//     int i;

//     lexer_advance(lexer);
//     lexer_advance(lexer);
//     lexer_skip_whitespaces(lexer);
//     i = 0;
//     while (!is_special(lexer->line[lexer->i + i]))
//         i++;
//     herdoc = ft_malloc(i * sizeof(char) + 1 + 3); // ghi popur l'instant
//     if (!herdoc)
//         NULL;
//     i = 0;
//     herdoc[i++] = '<';
//     herdoc[i++] = '<';
//     herdoc[i++] = ' ';
//     while (!is_special(lexer->c))
//     {
//         herdoc[i] = lexer->c;
//         lexer_advance(lexer);
//         i++;
//     }
//     herdoc[i] = '\0';
//     return (init_token(herdoc, HERE_DOC));
// }

// t_token *lexer_get_expansion(t_lexer *lexer)
// {
//     char *var;
//     // char *env_v;
//     int size;
//     int i;

//     lexer_advance(lexer);
//     size = 0;
//     while (ft_isalnum(lexer->line[lexer->i + size]))
//         size++;
//     var = ft_malloc(size * sizeof(char) + 1);
//     if (!var)
//         clean_exit(lexer, NULL);
//     i = 0;
//     while (i < size)
//     {
//         var[i] = lexer->c;
//         i++;
//         if (i < size)
//             lexer_advance(lexer);
//     }
//     var[i] = '\0';
//     // env_v = getenv(var);
//     // free_one(var);
//     return (init_token(var, EXPANSION));
//     // return (init_token(env_v, EXPANSION));
// }

// t_token *lexer_get_squote(t_lexer *lexer)
// {
//     char *squote;
//     int quote_size;

//     lexer_advance(lexer);
//     quote_size = get_q_size(lexer, 39);
//     if (!(*get_parser_check()))
//         return (lexer_error_advance(lexer));
//     squote = ft_malloc(quote_size * sizeof(char) + 1);
//     if (!squote)
//         clean_exit(lexer, NULL); // al marjo t freeyi w t exit in a clean
//     int i = 0;
//     while (i < quote_size)
//     {
//         squote[i] = lexer->c;
//         lexer_advance(lexer);
//         i++;
//     }
//     squote[i] = '\0';
//     lexer_advance(lexer);
//     return (init_token(squote, SQUOTE));
// }

// t_token *lexer_get_dquote(t_lexer *lexer)
// {
//     char *quote;
//     int quote_size;

//     lexer_advance(lexer);
//     quote_size = get_q_size(lexer, '"');
//     if (!(*get_parser_check()))
//         return (lexer_error_advance(lexer));
//     quote = ft_malloc((quote_size + 1) * sizeof(char));
//     if (!quote)
//         clean_exit(lexer, NULL); // al marjo t freeyi w t exit in a clean way
//     int j = 0;
//     while (j < quote_size)
//     {
//         quote[j] = lexer->c;
//         lexer_advance(lexer);
//         j++;
//     }
//     quote[j] = '\0';
//     lexer_advance(lexer);
//     return (init_token(quote, DQUOTE));
// }

// t_token *lexer_error_advance(t_lexer *lexer)
// {
//     while (lexer->c)
//     {
//         if (lexer->i == lexer->line_size - 1)
//             break;
//         lexer_advance(lexer);
//     }
//     return (NULL);
// }