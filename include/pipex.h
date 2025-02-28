/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:58:48 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/28 12:16:42 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

/**
 * This should be updated!
 */
# define PUSAGE "Usage:\n ./pipex infile cmd1 cmd2 outfile"

/**
 * @brief Error codes for pipex
 * @param INPUTFILEERR Error opening input file
 * @param OUTPUTFILEERR Error opening output file
 * @param CMDNOTFOUND Command not found in path
 */
typedef enum e_err
{
	INPUTFILEERR = (1 << 0),
	OUTPUTFILEERR = (1 << 1),
	CMDNOTFOUND = (1 << 2),
}	t_err;

/**
 * @brief Command descriptor
 * @note Array of strings (null-terminated)
 */
typedef char	**t_cmddesc;

/**
 * @brief Exit clause to print usage on error
 * @param err Error code
 */
int			exit_clause(int err);

/**
 * @brief Cleanup function to close fds and free memory
 * @param fds File descriptors to close
 * @param lst List to free
 */
// void		cleanup(int fds[2], t_list *lst);
void		cleanup(int fds[2], int pipe[2], t_list *lst, char *error);

/**
 * @brief Subfunction to read stdin to pipe
 * @param endstr End string to stop reading
 * @param child_input File descriptor to read from
 * @param child_output File descriptor to write to
 */
void		read_ln_heredoc(char *endstr, int child_input, int child_output);

/**
 * @brief Setup heredoc for pipex
 * @param endstr End string to stop reading
 * @param io_fds File descriptors to read/write to
 * @return pid of child process (useful for waiting)
 */
int			setup_heredoc(char *endstr, int *io_fds);

/**
 * @brief Parse flags for pipex
 * @param argc Pointer to argc
 * @param argv Pointer to argv
 * @param io_fds File descriptors to read/write to
 * @param err Error code
 * @return Flag for pipex
 */
int			parse_flags(int *argc, char ***argv, int *io_fds, int *err);

/**
 * @brief Execute commands in pipex
 * @param iter Iteration counter max and index
 * @param cmdv List of commands
 * @param io_fd File descriptors to read/write to
 * @return status of last child process
 */
int			execute_commands(int iter[2], t_list *cmdv, int io_fd[2]);

/**
 * @brief Closes unused pipes/fds and executes child process
 * @param n Iteration counter max and index
 * @param cmdv List of commands
 * @param io_fd File descriptors to read/write to
 * @param pipe Pipe to write to
 */
void		child_process_prep(int n[2], t_list *cmdv,
				int io_fd[2], int pipe[2]);

// cmd prep
/**
 * @brief checks if cmd is a valid file and is executable
 * @param cmd Command to check
 * @return 1 if valid, 0 if not
 */
int			check_cmdpath(char *cmd);

/**
 * @brief Get path from environ
 * @return List of paths
 */
char		**get_path(void);

/**
 * @brief Get path of command
 * @param cmd Command to get path of
 * @return Path of command
 */
char		*get_cmdpath(char *cmd);

// queue
/**
 * @brief Enqueue commands into a list
 * @param argc Number of arguments
 * @param argv List of arguments
 * @param err Error code
 * @return List of commands
 */
t_list		*enqueue_cmds(int argc, char **argv, int *err);

/**
 * @brief Push a valid command into a list
 * @param lst List to push to
 * @param cmd Command to push
 * @return 1 if successful, 0 if not
 */
int			push_validcmd(t_list **lst, char *cmd);

/**
 * @brief Get a valid command (splits the command)
 * @param cmd Command to split
 * @return array of command and args
 */
t_cmddesc	get_validcmd(char *cmd);

/**
 * @brief Print command error
 * @param cmd Command to print error for
 */
void		print_cmd_err(char *cmd);

// utils
/**
 * @brief Delete a split array
 * @param splt Array to delete
 */
void		ft_deletesplit(char **splt);

// file validation
/**
 * @brief Validate output file
 * @param path Path to output file
 * @param error Error code
 * @param flag Flag for pipex
 * @return fd of output file
 */
int			validate_outputfile(char *path, int *error, int flag);

/**
 * @brief Validate input file
 * @param path Path to input file
 * @param error Error code
 * @return fd of input file
 */
int			validate_inputfile(char *path, int *error);

#endif