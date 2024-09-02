# minishell
42's minishell w/ Molasz

Basically, a very basic (VERY) re-implementation of bash and some of its built-ins. Try it yourself! It even curls the readline for ya :D

## features

env vars (not profoundly), pipeage, redirs, hdocs (quits at >16, just like mr. bash!), PATH-finding, history (not a file tho), and probably even AND/OR operators although they might be working in reverse? it's the bonus part of the project and its other component was round brackets (which we didn't do), so we've decided to abandon the idea (because these two things are graded in a way where if you don't have one the other won't count).

## how-to-build?

Deps: build-essentials, curl

Instructions: clone the repo, run make inside of it. Exec with ./minishell

# Known issues
too many open files breaks everything and doesn't repair itself like it does in bash. probably, an easy fix would be to make it exit upon erroring to just not concern ourselves with handling errors outside of the subject's allowed functions. unsetting $HOME and doing a cd ~/something produced a double-free crash
