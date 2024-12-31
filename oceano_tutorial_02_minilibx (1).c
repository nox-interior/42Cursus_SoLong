# include "./mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>

// IMPORTANT: compilation
// gcc -Wall -Werror -Wextra oceano_tutorial_02_minilibx.c libft/libft.a mlx/libmlx.a 
// mlx/libmlx_Linux.a -lXext -lX11

#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

// KEYPRESS EVENT

// #define MLX_ERROR       1
// #define WINDOW_WIDTH    400
// #define WINDOW_HEIGHT   400


/*
 * MLX_STRUCT
 * I stock all the data into a struct
 * because the handler function takes 
 * (void *)pointer_to_data
 * I need therefore this gimmick to 
 * pass more elements in one-go
*/
typedef struct s_mlx_data
{
    void	*mlx_ptr;
    void	*win_ptr;
}               t_mlx_data;

/*
 * HANDLER FUNCTION 
 * Every time a key is pressed this function is called
 *
 * KEYSYM vs KEYCODE
 * A keycode is a hardware-specific code sent by the keyboard for a key press, 
 * while a keysym is its abstract representation, 
 * often used in software to identify the key regardless of hardware.
 * 🚨 MinilibX mac uses keycodes 🚨
*/
// int	handle_input(int keysym, t_mlx_data *data)
// {
//     //Check the #defines
//     //find / -name keysym.h 2>/dev/null
//     //find / -name keysymdef.h 2>/dev/null
//     if (keysym == XK_Escape)
//     {
//         printf("The %d key (ESC) has been pressed\n\n", keysym);
//         mlx_destroy_window(data->mlx_ptr, data->win_ptr);
//         mlx_destroy_display(data->mlx_ptr);
//         free(data->mlx_ptr);
//         exit(1);
//     }
//     printf("The %d key has been pressed\n\n", keysym);
//     return (0);
// }


// int	main(void)
// {
//     t_mlx_data	data;

//     data.mlx_ptr = mlx_init();
//     if (data.mlx_ptr == NULL)
//         return (MLX_ERROR);
//     data.win_ptr = mlx_new_window(data.mlx_ptr, 
//                                 WINDOW_WIDTH, 
//                                 WINDOW_HEIGHT,
//                                 "My first window!");
//     if (data.win_ptr == NULL)
//     {
//         mlx_destroy_display(data.mlx_ptr);
//         free(data.mlx_ptr);
//         return (MLX_ERROR);
//     }

//     /*
//      * HOOKS
//      *  "Hooking into events" (react to events)
//      * When i press a key, handle_input() is triggered
//      * 💡 Every event is linked to its own prototype handler 💡
//     */
//     mlx_key_hook(data.win_ptr, 
//                 handle_input, 
//                 &data);

//     // Leave the control to the EVENT LOOP
//     mlx_loop(data.mlx_ptr);
// }

// // int		mlx_key_hook(t_win_list *win,int (*funct)(),void *param)

// // created function
// int  handle_input(int keysym, t_mlx_data *data);

// // event prototype function
// int (*f)(int keycode, void *param);

// HOOK MASK

#include <X11/X.h>

// #define WIN_WIDTH 800
// #define WIN_HEIGHT 600

// typedef struct  s_data
// {
//     void        *mlx_ptr;
//     void        *win_ptr;
// }               t_data;

// int     button_press(int button, int x, int y, t_data *data)
// {
// 	(void)data;
//     if (button == 1)
//         printf("Left mouse button pressed at (%d, %d)!\n", x, y);
//     else if (button == 3)
//         printf("Right mouse button pressed at (%d, %d)!\n", x, y);

//     return (0);
// }

// int     main(void)
// {
//     t_data  data;

//     data.mlx_ptr = mlx_init();
//     data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "MLX Window");

//     /*
//      * MLX_HOOK
//      * Handle both left and right mouse button presses with the same function.
//      * 🚨If remove the mask, hook won't work🚨
//      *
//      * TL;DR
//      * In the X11 system (on which MiniLibX is based), events and event masks are two distinct things:

//             Events (like ButtonPress): Describe the actual event type, such as pressing a button or moving the mouse.

//             Event Masks (like ButtonPressMask): Are filters that determine which types of events a program wants 
//             to listen for. By setting a specific mask, you're saying, "Notify me when this type of event happens."

//         When you use mlx_hook(), specifying both the event and its corresponding mask ensures that you:
//         Precisely define the event you're interested in (ButtonPress for a mouse button being pressed).
//         Tell the X11 system that you want to be notified about this event by setting the appropriate filter (ButtonPressMask).

//         🤔 Wait but why? 🤔
//      * Event Mask (Filter 1): It's the first layer of filtering. When you set a mask, you're essentially telling the X11 system,
//      *      "I'm interested in these types of events. Please notify me when they occur." 
//      * Without the right mask set, the system won't even forward the event to your application.

//        Event Name (Filter 2): Once the event gets through the mask and is delivered to your application, 
//         you then have handler functions (like your button_press function) which handle specific event types 
//         (like ButtonPress). This is where you react based on the exact event that occurred.

//         In the context of mlx_hook(), you're setting up both layers of filtering. 
//         💡 You specify the mask to ensure X11 sends the event to your program, 
//         💡 and then your handler function responds based on the specific event name (every event has its how prototype)
//      * 
//     */
//     mlx_hook(data.win_ptr, 
//             ButtonPress, 
//             ButtonPressMask,
//             &button_press, 
//             &data);

//     mlx_loop(data.mlx_ptr);
//     return (0);
// }

// LOOP HOOKS
#include <unistd.h>

typedef struct  sdata 
{
    void        *mlx;
    void        *win;
    int         color;
}               tdata;


int f(int keysym, tdata *data)
{
	//(void)data;
    printf("Pressed %d\n", keysym);
    //sleep to appreciate loop_hook stopping
    sleep(2);
    return 1;
}



int     change_color(tdata *data)
{
    // Fill the window with the current color
	//mlx_clear_window(data->mlx, data->win);
    mlx_string_put(data->mlx, data->win, 150, 150, data->color, "Color Changing Window!");

    // Cycle through some basic colors: RED, GREEN, BLUE
    if (data->color == 0xFF0000)        // If it's red
        data->color = 0x00FF00;        // Change to green
    else if (data->color == 0x00FF00)   // If it's green
        data->color = 0x0000FF;        // Change to blue
    else
        data->color = 0xFF0000;        // Otherwise, go back to red

    return (0);
}

int     main(void)
{
    tdata  data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 400, 400, "Sample Window");
    data.color = 0xFF0000;  // Start with red color

    mlx_key_hook(data.win,f, &data);

    //mlx_loop_hook is one hook that is triggered when there's no event processed.
    //Cool to have a continuous rendering on the screen
   	mlx_loop_hook(data.mlx, change_color, &data);
    mlx_loop(data.mlx);

    return (0);
}
