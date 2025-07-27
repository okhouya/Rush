/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beginner <marvin@1337.ma>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:00:00 by beginner          #+#    #+#             */
/*   Updated: 2025/07/27 14:00:00 by beginner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// ---------------------- PRINTING THE GRID ----------------------
void	print_grid(int grid[4][4])
{
	char c;
	int i = 0;
	while (i < 4)
	{
		int j = 0;
		while (j < 4)
		{
			c = grid[i][j] + '0';
			write(1, &c, 1);
			if (j < 3)
				write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

// ---------------------- COUNT VISIBLE TOWERS ----------------------
int	count_visible(int *line)
{
	int i = 1;
	int count = 1;
	int max = line[0];
	while (i < 4)
	{
		if (line[i] > max)
		{
			count++;
			max = line[i];
		}
		i++;
	}
	return (count);
}

// ---------------------- CHECK VISIBILITY FOR ROW ----------------------
int	check_row(int grid[4][4], int row, int left, int right)
{
	int line[4];
	int rev[4];
	int i = 0;
	while (i < 4)
	{
		line[i] = grid[row][i];
		rev[i] = grid[row][3 - i];
		i++;
	}
	if (count_visible(line) != left)
		return (0);
	if (count_visible(rev) != right)
		return (0);
	return (1);
}

// ---------------------- CHECK VISIBILITY FOR COLUMN ----------------------
int	check_col(int grid[4][4], int col, int top, int bottom)
{
	int line[4];
	int rev[4];
	int i = 0;
	while (i < 4)
	{
		line[i] = grid[i][col];
		rev[i] = grid[3 - i][col];
		i++;
	}
	if (count_visible(line) != top)
		return (0);
	if (count_visible(rev) != bottom)
		return (0);
	return (1);
}

// ---------------------- CHECK DUPLICATES ----------------------
int	is_valid(int grid[4][4], int row, int col, int num)
{
	int i = 0;
	while (i < 4)
	{
		if ((i != col && grid[row][i] == num) || (i != row && grid[i][col] == num))
			return (0);
		i++;
	}
	return (1);
}

// ---------------------- SOLVER (BACKTRACKING) ----------------------
// ---------------------- SOLVER (BACKTRACKING) ----------------------
int	solve(int grid[4][4], int pos, int *top, int *bottom, int *left, int *right)
{
	if (pos == 16)
	{
		int i = 0;
		while (i < 4)
		{
			if (!check_row(grid, i, left[i], right[i]) || !check_col(grid, i, top[i], bottom[i]))
				return (0);
			i++;
		}
		return (1);
	}

	int row = pos / 4;
	int col = pos % 4;
	for (int num = 1; num <= 4; num++)
	{
		if (is_valid(grid, row, col, num))
		{
			grid[row][col] = num;
			if (solve(grid, pos + 1, top, bottom, left, right))
				return (1);
			grid[row][col] = 0;
		}
	}
	return (0);
}

// ---------------------- PARSE INPUT ----------------------
int	parse_input(char *str, int *arr)
{
	int i = 0;
	while (*str)
	{
		if (*str >= '1' && *str <= '4')
			arr[i++] = *str - '0';
		else if (*str != ' ')
			return (0);
		str++;
	}
	return (i == 16);
}

// ---------------------- MAIN FUNCTION ----------------------
int	main(int argc, char **argv)
{
	int grid[4][4] = {0};
	int views[16];

	if (argc != 2 || !parse_input(argv[1], views))
		return (write(1, "Error\n", 6));

	int *top = views;
	int *bottom = views + 4;
	int *left = views + 8;
	int *right = views + 12;

	if (!solve(grid, 0, top, bottom, left, right))
		write(1, "Error\n", 6);
	else
		print_grid(grid);
	return (0);
}

