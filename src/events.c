/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:51:19 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/22 13:51:24 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/fdf.h"

int	mouse_move(int X, int Y, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;

	if (X > WINX || X < 0 || Y > WINY || Y < 0)
		return(0);
	printf("Mouse Press [%d][%d]\n", X,Y);
	return(0);
}

int	mouse_release(int button, int X, int Y, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	printf("Mouse Release[%d] - [%d][%d]\n", button, X,Y);
	return(0);
}

int	mouse_press(int button, int X, int Y, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	printf("Mouse Press[%d] - [%d][%d]\n", button, X,Y);

	if (button == 4)
	{
		// Zoom IN
		meta->map.scale = meta->map.scale + 1;
		draw_map(meta);
	}
	if (button == 5)
	{
		// Zoom OUT
		if (meta->map.scale > 1)
			meta->map.scale = meta->map.scale - 1;
		draw_map(meta);
	}
	return (0);

}
//int	key_hook(int keycode, t_meta *meta)

int	key_press(int key, void *param)
{
	t_point		dot;
	t_point		start;
	t_point		end;
	int 		i;
	t_meta	*meta;

	meta = (t_meta *)param;
	printf("Keycode Press [%d]\n", key);	
	if (key == KEY_ESC)
	{

		mlx_destroy_window(meta->vars.mlx, meta->vars.win);
		free(meta->map.points);
		free(meta->map.proyect3D);
		free(meta->map.proyect2D);
		exit(0);	
	}
	if (key == KEY_1)
	{
		generate_background(meta, 0x000000);
		draw_bitmap(meta, 0, 0);
	}
	if (key == KEY_2)
	{
		start.axis[x] = 0;
		start.axis[y] = 0;
		start.color = 0x005500;
		end.axis[x] = WINX;
		end.axis[y] = WINY;
		while (end.axis[x] > 0)
		{
			draw_line(meta, start, end);
			end.axis[x] -= 20;
		}
		draw_bitmap(meta, 0, 0);
	}
	if (key == KEY_3)
	{
		start.axis[x] = WINX;
		start.axis[y] = 0;
		start.color = 0xFF5500;
		end.axis[x] = 0;
		end.axis[y]= WINY;

		while (end.axis[x] < WINX)
		{
			draw_line(meta, start, end);
			end.axis[x] += 20;
		}
		draw_bitmap(meta, 0, 0);
	}
	if (key == KEY_4)
	{	
		dot.axis[x] = 300;
		dot.axis[y] = 150;
		dot.color = VERDE;
		draw_dot(meta, dot, 10);
		draw_bitmap(meta, 0, 0);
	}
	if (key == KEY_5)
	{
		my_cube(meta);
		draw_bitmap(meta, 0, 0);
	}
	if (key == KEY_6)
	{
		static int ang;
		ang += 1;
		meta->map.ang[x] = ang;
		meta->map.ang[y] = ang;
		meta->map.ang[z] = 0;
		draw_map(meta);
	}
	if (key == KEY_SUM)
	{
		// Zoom IN
		meta->map.scale = meta->map.scale + 1;
		draw_map(meta);
	}
	if (key == KEY_RES)
	{
		// Zoom OUT
		if (meta->map.scale > 1)
			meta->map.scale = meta->map.scale - 1;
		draw_map(meta);
	}
	if (key == KEY_DOWN)
	{
		if (meta->map.ang[x] == 360)
			meta->map.ang[x] = 0;
		meta->map.ang[x] = meta->map.ang[x] + 1;	
		draw_map(meta);
	}	
	if (key == KEY_UP)
	{
		if (meta->map.ang[x] == 0)
			meta->map.ang[x] = 360;
		meta->map.ang[x] = meta->map.ang[x] - 1;	
		draw_map(meta);
	}		
	if (key == KEY_LEFT)
	{
		if (meta->map.ang[y] == 360)
			meta->map.ang[y] = 0;
		meta->map.ang[y] = meta->map.ang[y] + 1;	
		draw_map(meta);
	}	
	if (key == KEY_RIGHT)
	{
		if (meta->map.ang[y] == 0)
			meta->map.ang[y] = 360;
		meta->map.ang[y] = meta->map.ang[y] - 1;	
		draw_map(meta);
	}	
	if (key == KEY_Q)
	{
		if (meta->map.ang[z] == 360)
			meta->map.ang[z] = 0;
		meta->map.ang[z] = meta->map.ang[z] + 1;	
		draw_map(meta);
	}		
	if (key == KEY_W)
	{
		if (meta->map.ang[z] == 0)
			meta->map.ang[z] = 360;
		meta->map.ang[z] = meta->map.ang[z] - 1;	
		draw_map(meta);
	}			
	return(0);
}
