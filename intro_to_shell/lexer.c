#include "../include/minishell.h"

t_lexer *init_lexer(char *line)
{
    t_lexer *lexer;

    lexer->line = line;
    lexer->i = 0;
    lexer->c = line[0];
    return (lexer);
}

void lexer_advance(t_lexer *lexer)
{
    if (lexer && lexer->c && lexer->line[lexer->i + 1])
    {
        lexer->i++;
        lexer->c = lexer->line[lexer->i];
    }
}

void lexer_skip_whitespaces(t_lexer *lexer)
{
    while (is_space(lexer->c))
        lexer_advance(lexer);
}

t_token *lexer_get_word(t_lexer *lexer)
{
    char *word;
    int i;

    i = 0;
    while (ft_isalnum(lexer->line[lexer->i + i]))
        i++;
    word = malloc(i * sizeof(char) + 1);
    if (!word)
        return (NULL); // al marjo t freeyi w t exit in a clean
    i = 0;
    while (ft_isalnum(lexer->c))
    {
        word[i] = lexer->c;
        lexer_advance(lexer);
        i++;
    }
    word[i] = '\0';
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

t_token *lexer_get_dquote(t_lexer *lexer)
{
    char *quote;
    char *env_var;
    int quote_size;
    char **var;
    int i;
    int j;

    lexer_advance(lexer);


    // var
    quote_size = get_q_size(lexer);
    quote = malloc(quote_size * sizeof(char) + 1);
    if (!quote)
        clean_exit(lexer, NULL); // al marjo t freeyi w t exit in a clean way
    i = 0;
    while (lexer->c != '"')
    {
        if (lexer->c == '$')
        {
            env_var = getenv(get_env_var(lexer));
            quote = ft_strjoin(quote, env_var);// tkhrbiq
            // j = 0;
            // while (env_var[j])
            // {
            //     quote[i + j] = env_var[j];
            //     j++;
            // }
        }
        quote[i] = lexer->c;
        lexer_advance(lexer);
        i++;
    }
    quote[i] = '\0';
    return (init_token(quote, WORD));
}

int get_q_size(t_lexer *lexer)
{
    int i;

    i = 0;
    while (lexer->line[lexer->i + i] != '"')
    {
        if (lexer->line[lexer->i + i] == '$')
        {
            j = 0;
            while (ft_isalnum(lexer->line[lexer->i + i + j]))
            {
                j++;
            }
        }
        i++;
    }
}

char *get_env_var(t_lexer *lexer)
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
    return (var);
}

t_token *lexer_advance_current(t_lexer *lexer, int type)
{
    char *token;

    token = malloc(sizeof(char) + 1);
    if (!token)
        return (NULL);/// a revoir
    token[0] = lexer->c;
    token[1] = '\0';
    lexer_advance(lexer);
    return (token);
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

t_token *lexer_next_token(t_lexer *lexer)
{
    while (lexer->c)
    {
        lexer_skip_whitespaces(lexer);
        if (ft_isalnum(lexer->c))
            return (lexer_advance_with(lexer, lexer_get_word(lexer)));
        if (lexer->c == '&')
            if (lexer->line[lexer->i + 1] == '&')
                return (lexer_advance_with2(lexer, init_token("&&", AND)));
        if (lexer->c == '|')
            if (lexer->line[lexer->i + 1] == '|')
                return (lexer_advance_with2(lexer, init_token("||", OR)));
            return (lexer_advance_current(lexer, PIPE));
        if (lexer->c == '>')
            if (lexer->line[lexer->i + 1] == '>')
                return (lexer_advance_with2(lexer, init_token(">>", APPEND)));
            return (lexer_advance_current(lexer, OUTPUT_RED));
        if (lexer->c == '<')
            if (lexer->line[lexer->i + 1] == '<')
                return (lexer_advance_with(lexer, lexer_get_heredoc(lexer)));
            return (lexer_advance_current(lexer, INPUT_RED));
        if (lexer->c == '"')
            return (lexer_advance_with(lexer, lexer_get_dquote(lexer)));
        if (lexer->c == '\'')
            return (lexer_advance_with(lexer, lexer_get_squote(lexer)));
        if (lexer->c == '$')
            return (lexer_advance_with(lexer, lexer_get_expansion(lexer)));
    }
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

void clean_exit(t_lexer *lexer, t_token *token)
{
    exit(1);
}