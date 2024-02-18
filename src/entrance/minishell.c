/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmoretti <brmoretti@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:19:43 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/18 11:06:06 by brmoretti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile int	g_last_signal;

int	main(void)
{
	signals_initializer();
	environ_initializer();
	static_pwd(malloc_pwd(), 0);
	while (true)
	{
		g_last_signal = 0;
		parser(prompt());
	}
	return (EXIT_SUCCESS);
}

char	*prompt(void)
{
	char	*input;

	is_after_prompt(0);
	input = readline("minishell>$ ");
	is_after_prompt(1);
	add_history(input);
	if (!input)
		input = ft_strdup("exit");
	return (input);
}

void	parser(char *input)
{
	t_list	*tokens;
	t_ast	*root;

	tokens = tokenizer(input);
	free(input);
	if (!tokens)
		return ;
	ft_lstiter(tokens, trim_edges);
	if (grammar_checker(tokens))
		return ;
	if (!heredoc_substitution(tokens))
		return ;
	root = ast_constructor(tokens);
	if (!root)
		return ;
	token_list_holder(NULL, 0, 1);
	ast_holder(root, 0);
	execution(root);
	ast_holder(NULL, 1);
}
