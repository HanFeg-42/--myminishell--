/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:13:35 by marvin            #+#    #+#             */
/*   Updated: 2024/11/09 13:44:55 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_elmt;
	t_list	*tmp;
	void	*err;

	new_elmt = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		err = f(lst->content);
		tmp = ft_lstnew(err);
		if (!tmp)
		{
			free(err);
			ft_lstclear(&new_elmt, del);
			return (NULL);
		}
		ft_lstadd_back(&new_elmt, tmp);
		lst = lst->next;
	}
	return (new_elmt);
}
