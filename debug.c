#include "minirt.h"

void	leaks_miniRT(int idx)
{
	for (int i = 0; i < 20; i++)
		printf("%d", idx);
	printf("\n");
	system("leaks miniRT | grep LEAK");
	for (int i = 0; i < 20; i++)
		printf("%d", idx);
	printf("\n");
}

void	print_scene(t_scene *s)
{
	printf(
		"A : %.1f %.1f,%.1f,%.1f\n",
		s->ambient.ratio,
		s->ambient.color.x,
		s->ambient.color.y,
		s->ambient.color.z
	);
	printf(
		"C : %.1f,%.1f,%.1f %.1f,%.1f,%.1f %d\n",
		s->camera.coor.x,
		s->camera.coor.y,
		s->camera.coor.z,
		s->camera.orientation.x,
		s->camera.orientation.y,
		s->camera.orientation.z,
		s->camera.fov
	);
	printf(
		"L : %.1f,%.1f,%.1f %.1f\n",
		s->light.coor.x,
		s->light.coor.y,
		s->light.coor.z,
		s->light.ratio
	);
	t_obj	*obj = s->objs;
	while (obj)
	{
		if (obj->type == SPHERE)
		{
			t_sphere	*sp = obj->element;
			printf(
				"sp : %.1f,%.1f,%.1f %.1f %.1f,%.1f,%.1f\n",
				sp->coor.x,
				sp->coor.y,
				sp->coor.z,
				sp->radius,
				sp->color.x,
				sp->color.y,
				sp->color.z
			);
		}
		else if (obj->type == PLANE)
		{
			t_plane	*pl = obj->element;
			printf(
				"pl : %.1f,%.1f,%.1f %.1f,%.1f,%.1f %.1f,%.1f,%.1f\n",
				pl->coor.x,
				pl->coor.y,
				pl->coor.z,
				pl->orientation.x,
				pl->orientation.y,
				pl->orientation.z,
				pl->color.x,
				pl->color.y,
				pl->color.z
			);
		}
		else if (obj->type == CYLINDER)
		{
			t_cylinder	*cy = obj->element;
			printf(
				"cy : %.1f,%.1f,%.1f %.1f,%.1f,%.1f %.1f %.1f %.1f,%.1f,%.1f\n",
				cy->coor.x,
				cy->coor.y,
				cy->coor.z,
				cy->orientation.x,
				cy->orientation.y,
				cy->orientation.z,
				cy->radius,
				cy->height,
				cy->color.x,
				cy->color.y,
				cy->color.z
			);
		}
		obj = obj->next;
	}
}
