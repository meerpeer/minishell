#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*current;

	if (!lst)
		return (0);
	new_lst = ft_lstnew(f(lst->content));
	if (!new_lst)
		return (0);
	current = new_lst;
	lst = lst->next;
	while (lst)
	{
		current->next = ft_lstnew(f(lst->content));
		current = current->next;
		if (!current)
		{
			ft_lstclear(&new_lst, del);
			return (0);
		}
		lst = lst->next;
	}
	return (new_lst);
}
