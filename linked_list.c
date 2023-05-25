#include "shell.h"

void alias_list_free(alias_t *head);
/*alias_t *alias_add_end(alias_t **head, char *name, char value);*/
list_t *add_node_end(list_t **head, char *dir);
void list_free(list_t *head);

/**
 * alias_add_end - function that adds a node to the end of alias_t linkedlist
 * @head: pointer to the head of the list_t list
 * @name: this is the name of the new alias to be added
 * @value: this is the value of he new alias to be added
 *
 * Return: returns NULL if an error occurs. otherwise ptr to the new node
 */
alias_t *alias_add_end(alias_t **head, char *name, char *value)
{
	alias_t *new_node;
	alias_t *last;

	new_node = malloc(sizeof(alias_t));
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->val = value;
	_strcpy(new_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}

/**
 * add_node_end - function that adds a node to the end of a linkedlist
 * @head: pointer to the head of the linked list
 * @dir: the directory path containing the new node
 *
 * Return: returns NULL if an error occurs. otherwise a ptr to the new node
 */
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *new_node;
	list_t *last;

	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->dir = dir;
	new_node->next = NULL;

	if (!new_node)
	{
		return (NULL);
	}
	new_node->dir = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}

/**
 * alias_list_free -  function that frees alias linked list
 * @head: this is the head of the alias_t list
 */
void alias_list_free(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->val);
		free(head);
		head = next;
	}
}

/**
 * list_free - function that frees a list_t linked list
 * @head: this is the head of the list_t list
 */
void list_free(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
