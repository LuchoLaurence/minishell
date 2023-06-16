#include "minishell.h"

/*  void ft_free_ptr frees a simple pointer */
void    ft_free_ptr(void *ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = NULL;
    }
}

/*static void ft_free_envp(t_struct *s)
{
    (void) s;
    void    *temp;

    if (!s)
        return ;
    temp = s->envp;
    while (temp)
    {
        ft_free_ptr((void *) temp->name);
        ft_free_tab((void **) temp->value);
        temp = temp->next;
    }
}*/

/*  void ft_free_everything frees everything */
/*void    ft_free_everything(t_struct *s)
{
    if (!s)
        return ;
    ft_free_ptr((void *)s);
}*/