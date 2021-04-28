//
// Created by osc on 21/04/2021.
//
#include <ui.h>

int main(void)
{
	t_ui    *ui;
	t_ui_win *win;
	t_ui_elem *button;

	ui = ui_init(UI_INIT_VIDEO, IMG_INIT_JPG | IMG_INIT_PNG);
	win = ui_add_window(ui, "Pak", 100, 100, 1500, 800,
					 UI_WINDOW_RESIZABLE,
					 UI_RENDERER_ACCELERATED | UI_RENDERER_PRESENTVSYNC,
					 ui_colorblock_1);
	button = ui_add_elem(win->content, 25, 25, 50, 50, 1,
					  ui_colorblock_2, UI_TRUE, NULL, NULL);
	button->store = ui_load_font("blackchancery/BLKCHCRY.TTF", 80);
	refresh_win(win);
	SDL_Delay(4000);
	ui_close_font(button->store);
	ui_close(ui);
	puts("Finished.");
	return 0;
}

/*
étape 1: tester l'initialisation de la librairie. Ok pour l'instant. 4 leaks inévitables (à ma connaissance)

étape 2: Créer une fenêtre.
-On malloc une ui_win.
-On l'ajoute à la liste des wins de l'ui fournie.
-On crée une fenêtre SDL selon les paramêtres fournis par l'utilisateur.
-Idem pour le renderer.
-On met à jour la taille réelle de la fenêtre.(win.width, win.length)
-On met un élément vierge dans le content de la fenêtre.(Tout est à NULL ou à false, sauf la taille en proportions, actual size qui n'est pas définie,
	sensible qui est à true, display priority et display func qui sont données par l'utilisateur.)
-On met à jour la taille réelle de l'elem content de la fenêtre.(0, 0, win.with, win.length)
-Ensuite ui_close fera comme avant la destruction de SDL et IMG, mais elle remarquera qu'il y a une fenêtre et appellera ui_free_window dessus.
-Cela aura pour effet de détruire la fenêtre SDL et le renderer.
-De supprimer l'élément content et tous ses sous éléments.
-Et enfin de supprimer la ui_win elle-même.

 étape 3: Définir et présenter un rendu.
-Dans l'étape 2, nous avions défini une fonction d'affichage dans le content
 de notre fenêtre mais celle-ci n'était jamais appelée ni présentée.
-On va donc d'abord ajouter un élément.
    Cela malloc un élément,
    on set son parent, sa win, ses proportions,
    sa disp priority, sa display func, et le reste à null.
    On l'ajoute ensuite à la liste de content.
    Puis on calcule et set son actual size rect.
-On appelle ui_resolve_and_refresh_win
    On appelle la display func de content.
    On appelle ensuite resolve_and_display_elem sur chacun
    de ses sub-elems:
        -Si l'élément traité a une display priority:
        -On active sa display func.
        -On rappelle la fonction sur chacun de ses
        sous-éléments.
	Deux rectangles auront ainsi été dessinés, celui de
    content et celui de l'elem ajouté.
    On appelle finalement SDL_RenderPresent
-Mais ça ne s'arrête pas là, car la ui_close sera différente.
	ui_remove_elem va se lancer de façon récursive.
 */
