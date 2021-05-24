if [[ -z $1 ]]
then
	echo "First give the name of the new interface element. If you think it will have a custom store free func, enter 'custom' as the second argument."
else
echo $'#include "ui.h"\n' > src/$1.c
if [[ -n $2 && $2 == 'custom' ]]
then
echo "void	ui_free_$1_store(void *to_free)
{

}
" >> src/$1.c
fi
echo "void	ui_display_$1(t_ui_elem *e)
{

}

void	ui_$1_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{

}

t_ui_elem	*ui_create_$1(t_ui_elem *parent, int x, int y)
{
	t_ui_elem	*new;

	new = ui_add_elem(parent, x, y, );
	return new;
}" >> src/$1.c
fi
