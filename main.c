#include <SDL2/SDL.h>
#include <stdio.h>
#include "renderer.h"
#include "microui.h"
//#include "memory.h"

static char logbuf[64000];
static int logbuf_updated = 0;
static float bg[3] = {137, 23, 233};




static void write_log(const char *text)
{
  if (logbuf[0])
  {
    strcat(logbuf, "\n");
  }
  strcat(logbuf, text);
  logbuf_updated = 1;
}
static void test_window(mu_Context *ctx)
{
  /* do window */
  if (mu_begin_window(ctx, "KanjoTux - Linux Cheat Base", mu_rect(0, 0, 300, 165)))
  {
    mu_Container *win = mu_get_current_container(ctx);
    win->rect.w = mu_max(win->rect.w, 100);
    win->rect.h = mu_max(win->rect.h, 100);

    mu_layout_set_next(ctx, mu_rect(5, 140, 40, 20), 0);
    if (mu_button(ctx, "Exit")) { 
        exit(0);
      }

    if (mu_header_ex(ctx, "Cheat Options", MU_OPT_EXPANDED))
    {
      mu_layout_row(ctx, 3, (int[]) { 86, -110, -1 }, 0);

      if (mu_button(ctx, "Inf Money")) { 
        system("gnome-terminal --execute sudo ./cheats/inf_money/inf_money");
        system("clear");
      }
      if (mu_button(ctx, "Sell Exploit")) { 
        system("gnome-terminal --execute sudo ./cheats/sell_exploit/sell_exploit");
        system("clear");
      }
      if (mu_button(ctx, "Coming Soon")) { 
        //valuechange = 1;
      }
    }
    mu_layout_set_next(ctx, mu_rect(5, 101, 290, 20), 0);
    if (mu_header_ex(ctx, "Useful Tools", MU_OPT_EXPANDED))
    {
      mu_layout_row(ctx, 3, (int[]) { 86, -110, -1 }, 0);

      if (mu_button(ctx, "Scanmem")) { 
        system("gnome-terminal --execute sudo scanmem");
      }
      if (mu_button(ctx, "GConqueror")) { 
        system("gnome-terminal --execute sudo gameconqueror");
      }
      if (mu_button(ctx, "PINCE")) { 
        system("gnome-terminal --execute [PINCE location]");
      }
    }

    

    /* background color sliders */
    /*
    if (mu_header_ex(ctx, "Background Color", MU_OPT_EXPANDED))
    {
      mu_layout_row(ctx, 2, (int[]){-78, -1}, 74);
      // sliders
      mu_layout_begin_column(ctx);
      mu_layout_row(ctx, 2, (int[]){46, -1}, 0);
      mu_label(ctx, "  R:");
      mu_slider(ctx, &bg[0], 0, 255);
      mu_label(ctx, "  G:");
      mu_slider(ctx, &bg[1], 0, 255);
      mu_label(ctx, "  B:");
      mu_slider(ctx, &bg[2], 0, 255);
      mu_layout_end_column(ctx);
      // color preview 
      mu_Rect r = mu_layout_next(ctx);
      mu_draw_rect(ctx, r, mu_color(bg[0], bg[1], bg[2], 255));
      char buf[32];
      sprintf(buf, "#%02X%02X%02X", (int)bg[0], (int)bg[1], (int)bg[2]);
      mu_draw_control_text(ctx, buf, r, MU_COLOR_TEXT, MU_OPT_ALIGNCENTER);
    }
    */

    mu_end_window(ctx);
  }
}

static int uint8_slider(mu_Context *ctx, unsigned char *value, int low, int high)
{
  static float tmp;
  mu_push_id(ctx, &value, sizeof(value));
  tmp = *value;
  int res = mu_slider_ex(ctx, &tmp, low, high, 0, "%.0f", MU_OPT_ALIGNCENTER);
  *value = tmp;
  mu_pop_id(ctx);
  return res;
}

static void style_window(mu_Context *ctx)
{
  static struct
  {
    const char *label;
    int idx;
  } colors[] = {
      {"text:", MU_COLOR_TEXT},
      {"border:", MU_COLOR_BORDER},
      {"windowbg:", MU_COLOR_WINDOWBG},
      {"titlebg:", MU_COLOR_TITLEBG},
      {"titletext:", MU_COLOR_TITLETEXT},
      {"panelbg:", MU_COLOR_PANELBG},
      {"button:", MU_COLOR_BUTTON},
      {"buttonhover:", MU_COLOR_BUTTONHOVER},
      {"buttonfocus:", MU_COLOR_BUTTONFOCUS},
      {"base:", MU_COLOR_BASE},
      {"basehover:", MU_COLOR_BASEHOVER},
      {"basefocus:", MU_COLOR_BASEFOCUS},
      {"scrollbase:", MU_COLOR_SCROLLBASE},
      {"scrollthumb:", MU_COLOR_SCROLLTHUMB},
      {NULL}};
}

static void process_frame(mu_Context *ctx)
{
  mu_begin(ctx);
  //style_window(ctx);
  //log_window(ctx);
  test_window(ctx);
  mu_end(ctx);
}

static const char button_map[256] = {
    [SDL_BUTTON_LEFT & 0xff] = MU_MOUSE_LEFT,
    [SDL_BUTTON_RIGHT & 0xff] = MU_MOUSE_RIGHT,
    [SDL_BUTTON_MIDDLE & 0xff] = MU_MOUSE_MIDDLE,
};

static const char key_map[256] = {
    [SDLK_LSHIFT & 0xff] = MU_KEY_SHIFT,
    [SDLK_RSHIFT & 0xff] = MU_KEY_SHIFT,
    [SDLK_LCTRL & 0xff] = MU_KEY_CTRL,
    [SDLK_RCTRL & 0xff] = MU_KEY_CTRL,
    [SDLK_LALT & 0xff] = MU_KEY_ALT,
    [SDLK_RALT & 0xff] = MU_KEY_ALT,
    [SDLK_RETURN & 0xff] = MU_KEY_RETURN,
    [SDLK_BACKSPACE & 0xff] = MU_KEY_BACKSPACE,
};

static int text_width(mu_Font font, const char *text, int len)
{
  if (len == -1)
  {
    len = strlen(text);
  }
  return r_get_text_width(text, len);
}

static int text_height(mu_Font font)
{
  return r_get_text_height();
}

int main(int argc, char **argv)
{

  system("clear");
  //Func_StockPid("pidof -s Kanjozoku\\ Game.");


  /* init SDL and renderer */
  SDL_Init(SDL_INIT_EVERYTHING);
  r_init();

  // system("clear");

  /* init microui */
  mu_Context *ctx = malloc(sizeof(mu_Context));
  mu_init(ctx);
  ctx->text_width = text_width;
  ctx->text_height = text_height;

  // system("clear");

  /* main loop */
  for (;;)
  {
    

    /* handle SDL events */
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
      switch (e.type)
      {
      case SDL_QUIT:
        exit(EXIT_SUCCESS);
        break;
      case SDL_MOUSEMOTION:
        mu_input_mousemove(ctx, e.motion.x, e.motion.y);
        break;
      case SDL_MOUSEWHEEL:
        mu_input_scroll(ctx, 0, e.wheel.y * -30);
        break;
      case SDL_TEXTINPUT:
        mu_input_text(ctx, e.text.text);
        break;

      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
      {
        int b = button_map[e.button.button & 0xff];
        if (b && e.type == SDL_MOUSEBUTTONDOWN)
        {
          mu_input_mousedown(ctx, e.button.x, e.button.y, b);
        }
        if (b && e.type == SDL_MOUSEBUTTONUP)
        {
          mu_input_mouseup(ctx, e.button.x, e.button.y, b);
        }
        break;
      }

      case SDL_KEYDOWN:
      case SDL_KEYUP:
      {
        int c = key_map[e.key.keysym.sym & 0xff];
        if (c && e.type == SDL_KEYDOWN)
        {
          mu_input_keydown(ctx, c);
        }
        if (c && e.type == SDL_KEYUP)
        {
          mu_input_keyup(ctx, c);
        }
        break;
      }
      }
    }

    /* process frame */
    process_frame(ctx);

    /* render */
    r_clear(mu_color(bg[0], bg[1], bg[2], 255));
    mu_Command *cmd = NULL;
    while (mu_next_command(ctx, &cmd))
    {
      switch (cmd->type)
      {
      case MU_COMMAND_TEXT:
        r_draw_text(cmd->text.str, cmd->text.pos, cmd->text.color);
        break;
      case MU_COMMAND_RECT:
        r_draw_rect(cmd->rect.rect, cmd->rect.color);
        break;
      case MU_COMMAND_ICON:
        r_draw_icon(cmd->icon.id, cmd->icon.rect, cmd->icon.color);
        break;
      case MU_COMMAND_CLIP:
        r_set_clip_rect(cmd->clip.rect);
        break;
      }
    }
    r_present();

    // system("clear");
  }
  

  return 0;
}
