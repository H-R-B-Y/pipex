
`./pipex file1 cmd1 cmd2 file2`
` < file1 cmd1 | cmd2 > file2`

read file1 into the stdin of cmd1 then the stdout of cmd1 is piped into the stdin of cm2 finally the stdout of cmd2 is written to file2.

```
If you have any doubt, handle the errors like the shell command:
< file1 cmd1 | cmd2 > file2
```

