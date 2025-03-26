#include "../include/minishell.h"


int is_special(int c)
{
	if (c == '\0' || ft_issapce(c)
        || c == '$' || c == '*' || c == '&' || c == '|'
        || c == '>' || c == '<' || c == 34 || c == 39
        || c == '(' || c == ')' || c == '{' || c == '}')
		return (1);
	return (0);
}

t_lexer *init_lexer(char *line)
{
    t_lexer *lexer;

    lexer = malloc(sizeof(t_lexer));
    if (!lexer)
        return (NULL);
    lexer->line = ft_strdup(line);
    lexer->i = 0;
    lexer->c = line[0];
    lexer->line_size = ft_strlen(line);
    return (lexer);
}

void lexer_advance(t_lexer *lexer)
{
    if (lexer && lexer->c) // && lexer->line[lexer->i + 1])
    {
        lexer->i++;
        lexer->c = lexer->line[lexer->i];
    }
}

void lexer_skip_whitespaces(t_lexer *lexer)
{
    while (ft_issapce(lexer->c))
        lexer_advance(lexer);
}

t_token *lexer_get_word(t_lexer *lexer)
{
    char *word;
    int i;

    i = 0;
    while (!is_special(lexer->line[lexer->i + i]))
        i++;
    word = malloc((i + 1 ) * sizeof(char) );
    if (!word)
        return (NULL); // al marjo t freeyi w t exit in a clean
    int j = 0;
    while (j < i)
    {
        word[j] = lexer->c;
        j++;
        if (j < i)
            lexer_advance(lexer);
    }
    word[j] = '\0';
    return (init_token(word, WORD));
}

t_token *lexer_get_heredoc(t_lexer *lexer)
{
    char *herdoc;
    int i;

    lexer_advance(lexer);
    lexer_advance(lexer);
    lexer_skip_whitespaces(lexer);
    i = 0;
    while (ft_isalnum(lexer->line[lexer->i + i]))
        i++;
    herdoc = malloc(i * sizeof(char) + 1 + 3); // ghi popur l'instant
    if (!herdoc)
        NULL;
    i = 0;
    herdoc[i++] = '<';
    herdoc[i++] = '<';
    herdoc[i++] = ' ';
    while (ft_isalnum(lexer->c))
    {
        herdoc[i] = lexer->c;
        lexer_advance(lexer);
        i++;
    }
    herdoc[i] = '\0';
    return (init_token(herdoc, HERE_DOC));
}

// t_token *lexer_get_dquote(t_lexer *lexer)
// {
//     char *quote;
//     char *env_var;
//     int quote_size;
//     char **var;
//     int i;
//     int j;
//     lexer_advance(lexer);
//     // var
//     quote_size = get_q_size(lexer);
//     quote = malloc(quote_size * sizeof(char) + 1);
//     if (!quote)
//         clean_exit(lexer, NULL); // al marjo t freeyi w t exit in a clean way
//     i = 0;
//     while (lexer->c != '"')
//     {
//         if (lexer->c == '$')
//         {
//             env_var = getenv(get_env_var(lexer));
//             quote = ft_strjoin(quote, env_var);// tkhrbiq
//             // j = 0;
//             // while (env_var[j])
//             // {
//             //     quote[i + j] = env_var[j];
//             //     j++;
//             // }
//         }
//         quote[i] = lexer->c;
//         lexer_advance(lexer);
//         i++;
//     }
//     quote[i] = '\0';
//     return (init_token(quote, WORD));
// }

int get_q_size(t_lexer *lexer)
{
    int i;

    i = 0;
    while (lexer->line[lexer->i + i] != '"')
    {
        // if (lexer->line[lexer->i + i] == '$')
        // {
        //     j = 0;
        //     while (ft_isalnum(lexer->line[lexer->i + i + j]))
        //     {
        //         j++;
        //     }
        // }
        i++;
    }
    return (i);
}

// char *get_env_var(t_lexer *lexer)
// {
//     char *var;
//     int size;
//     int i;
//     lexer_advance(lexer);
//     size = 0;
//     while (ft_isalnum(lexer->line[lexer->i + size]))
//         size++;
//     var = malloc(size * sizeof(char) + 1);
//     if (!var)
//         clean_exit(lexer, NULL);
//     i = 0;
//     while (ft_isalnum(lexer->c))
//     {
//         var[i] = lexer->c;
//         lexer_advance(lexer);
//         i++;
//     }
//     var[i] = '\0';
//     return (var);
// }

t_token *lexer_advance_current(t_lexer *lexer, int type)
{
    char *token;

    token = malloc(sizeof(char) + 1);
    if (!token)
        return (NULL);/// a revoir
    token[0] = lexer->c;
    token[1] = '\0';
    lexer_advance(lexer);
    return (init_token(token, type));
}

t_token *lexer_advance_with(t_lexer *lexer, t_token *token)
{
    lexer_advance(lexer);
    return (token);
}

t_token *lexer_advance_with2(t_lexer *lexer, t_token *token)
{
    lexer_advance(lexer);
    lexer_advance(lexer);
    return (token);
}


t_token *lexer_get_squote(t_lexer *lexer)
{
    char *squote;
    int i;

    lexer_advance(lexer);
    i = 0;
    while (lexer->line[lexer->i + i] != '\'')
        i++;
    squote = malloc(i * sizeof(char) + 1);
    if (!squote)
        clean_exit(lexer, NULL); // al marjo t freeyi w t exit in a clean
    i = 0;
    while (lexer->c != '\'')
    {
        squote[i] = lexer->c;
        lexer_advance(lexer);
        i++;
    }
    squote[i] = '\0';
    lexer_advance(lexer);
    return (init_token(squote, SQUOTE));
}

t_token *lexer_get_expansion(t_lexer *lexer)
{
    char *var;
    int size;
    int i;

    lexer_advance(lexer);
    size = 0;
    while (ft_isalnum(lexer->line[lexer->i + size]))
        size++;
    var = malloc(size * sizeof(char) + 1);
    if (!var)
        clean_exit(lexer, NULL);
    i = 0;
    while (ft_isalnum(lexer->c))
    {
        var[i] = lexer->c;
        lexer_advance(lexer);
        i++;
    }
    var[i] = '\0';
    return (init_token(getenv(var), WORD));
}

t_token *lexer_get_dquote(t_lexer *lexer)
{
    char *quote;
    int quote_size;
    int i;

    lexer_advance(lexer);
    quote_size = get_q_size(lexer);
    quote = malloc(quote_size * sizeof(char) + 1);
    if (!quote)
        clean_exit(lexer, NULL); // al marjo t freeyi w t exit in a clean way
    i = 0;
    while (lexer->c != '"')
    {
        quote[i] = lexer->c;
        lexer_advance(lexer);
        i++;
    }
    quote[i] = '\0';
    return (init_token(quote, DQUOTE));
}

void clean_exit(t_lexer *lexer, t_token *token)
{
    (void)lexer;
    (void)token;
    exit(1);
}

t_token *lexer_skip_comment(t_lexer *lexer)
{
    char *comment;
    int i;

    i = 0;
    while (lexer->line[lexer->i + i])
        i++;
    comment = malloc(sizeof(char) * i + 1);
    if (!comment)
        clean_exit(lexer, NULL);
    i = 0;
    while (lexer->c)
    {
        comment[i] = lexer->c;
        lexer_advance(lexer);
        i++;
    }
    comment[i] = '0';
    return (init_token(comment, COMMENT));
}
void exit_error()
{
    printf("ERROR\n");
    // exit(1);
}

t_token *lexer_next_token(t_lexer *lexer)
{
    while (lexer->c)
    {
        lexer_skip_whitespaces(lexer);
        if (lexer->c == '*')
            return (lexer_advance_current(lexer, STAR));
        if (lexer->c == '&')
        {
            if (lexer->line[lexer->i + 1] == '&')
                return (lexer_advance_with2(lexer, init_token("&&", AND)));
            exit_error();
        }
        if (lexer->c == '|')
        {
            if (lexer->line[lexer->i + 1] == '|')
                return (lexer_advance_with2(lexer, init_token("||", OR)));
            return (lexer_advance_current(lexer, PIPE));

        }
        if (lexer->c == '>')
        {
            if (lexer->line[lexer->i + 1] == '>')
                return (lexer_advance_with2(lexer, init_token(">>", APPEND)));
            return (lexer_advance_current(lexer, OUTPUT_RED));

        }
        if (lexer->c == '<')
        {
            if (lexer->line[lexer->i + 1] == '<')
                return (lexer_advance_with(lexer, lexer_get_heredoc(lexer)));
            return (lexer_advance_current(lexer, INPUT_RED));
        }
        if (lexer->c == '"')
            return (lexer_advance_current(lexer, DQUOTE));
        if (lexer->c == '\'')
            return (lexer_advance_current(lexer, SQUOTE));
        if (lexer->c == '(')
            return (lexer_advance_current(lexer, OPAREN));
        if (lexer->c == ')')
            return (lexer_advance_current(lexer, CPAREN));
        if (lexer->c == '{')
            return (lexer_advance_current(lexer, OBRACE));
        if (lexer->c == '}')
            return (lexer_advance_current(lexer, CBRACE));
        if (lexer->c == '$')
            return (lexer_advance_with(lexer, lexer_get_expansion(lexer)));
        if (lexer->c == '#')
            return (lexer_advance_with(lexer, lexer_skip_comment(lexer)));
        if (!is_special(lexer->c))
            return (lexer_advance_with(lexer, lexer_get_word(lexer)));
        if (lexer->i == lexer->line_size - 1)
            return (NULL);
        // lexer_advance(lexer);
    }
    return (NULL);
}
