/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoretti <bmoretti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:17:59 by bmoretti          #+#    #+#             */
/*   Updated: 2024/01/17 13:23:49 by bmoretti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_element	*search_and_or(t_list *tokens)
{
	t_token		*token;
	t_element	*el;

	el = tokens->last;
	while (el)
	{
		token = el->content;
		if (token->type == AND || token->type == OR)
			return (el);
		el = el->prev;
	}
	return (NULL);
}

t_ast	*ast_constructor(t_list *tokens)
{
	t_ast		*root;

	root = ft_calloc(1, sizeof(t_ast));
	if (!root)
		return (NULL); //panic tree
	ast_split_node(root, tokens, search_and_or(tokens));
	if (!root->type)
	{
		root->type = EXEC;
		root->exec = tokens;
	}
	return (root);
}
