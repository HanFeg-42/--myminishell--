## Minishell To-Do List

### ✅ Done
- [x] Prompt in heredoc
- [x] Handle signals in heredoc
- [x] Fix '&' to be treated as a normal character
- [x] Support `export y=$x` where `x="a    b"` (understand and fix spacing issue)
- [x] Handle `touch x=hi; export x=*` correctly (do not expand)
- [x] Fix `is_numeric` function
- [x] Fix `SIGQUIT` behavior in heredoc
- [x] Handle patterns like `'path/*'`, `'*/'`, etc. (use `d_entry` type)

### 🛠️ In Progress / To Do
- [ ] Fix syscall failure behavior
- [ ] Fix Norminette issues
- [ ] Understand ANSI-C quoting | positional parameters | type promotion in c
- [ ] Deepen understanding of signals
- [ ] Prevent `exit` from printing when run in a forked child
- [ ] Set up pipes during forking (not all at once); use fork → dup → close → repeat
- [ ] Create a unified cleanup function for heredoc and child processes
- [ ] Learn bit shifting
- [ ] Add `curr` & `start` variables in `lexer` struct to help calculate sizes easily
- [ ] expand here_doc file content regarding variables exported within the same line : export a=dada && << eof cat
- [ ] TODO: add a delimiter variable to the here_doc struct
- [ ] TODO: generate file name for heredoc in execution
- [ ] fix exit status overflow
