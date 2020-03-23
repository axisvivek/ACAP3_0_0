/*
 * Copyright (C) 2017-2020, Axis Communications AB, LUND, SWEDEN
 */

/*
 * Simple example application that demonstrates how axoverlay is used.
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <glib.h>
#include <cairo/cairo.h>
#include <axoverlay.h>

#define OVERLAY_WIDTH 500   // Surface size defined
#define OVERLAY_HEIGHT 500

#define PIE_RADIUS 250  //Circle radius
#define ANIMATION_FPS 1 // Frame set or update interval

#define M_PI 3.14

static GMainLoop *main_loop = NULL;
static gint animation_timer = -1;
static gdouble pie_angle = 0.0;
static gint overlay_id = -1;

static gboolean
update_overlay_cb(gpointer data)   // function for changing the pie angle
{
  GError *error = NULL;

  /* Update the angle of the pie shape */
  pie_angle += 5.0;
  if (pie_angle >= 360.0) {
    pie_angle -= 360.0;
  }

  /* Request a redraw of the overlay */
  axoverlay_redraw(&error);
  if (error != NULL) {
    /*
     * If redraw fails then it is likely due to that overlayd has
     * crashed. Don't exit instead wait for overlayd to restart and
     * for axoverlay to restore the connection.
     */
    printf("Failed to redraw overlay (%d): %s\n", error->code, error->message);
    g_error_free(error);
  }

  return G_SOURCE_CONTINUE;
}

static void
render_overlay_cb(gpointer render_context, gint id,
                   struct axoverlay_stream_data *stream,
                   enum axoverlay_position_type postype, gfloat overlay_x,
                   gfloat overlay_y, gint overlay_width, gint overlay_height,
                   gpointer user_data)
{
  cairo_t *cr = render_context;
  cairo_select_font_face (cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size (cr, 64.0);
  cairo_set_source_rgb (cr, 0.0, 0.0, 1.0);
  cairo_move_to (cr, 10.0, 50.0);
  cairo_show_text (cr, "Hello, Vivek");  
}

static void
signal_handler(gint signal_num)
{
  switch (signal_num) {
  case SIGTERM:
  case SIGABRT:
  case SIGINT:
    g_main_loop_quit(main_loop);
    break;
  default:
    break;
  }
}

static gboolean
signal_handler_init(void)
{
  struct sigaction sa = {0};

  if (sigemptyset(&sa.sa_mask) == -1) {
    printf("Failed to initialize signal handler: %s", strerror(errno));
    return FALSE;
  }

  sa.sa_handler = signal_handler;

  if ((sigaction(SIGTERM, &sa, NULL) < 0) ||
      (sigaction(SIGABRT, &sa, NULL) < 0) ||
      (sigaction(SIGINT, &sa, NULL) < 0)) {
    printf("Failed to install signal handler: %s", strerror(errno));
    return FALSE;
  }

  return TRUE;
}

int
main(int argc, char **argv)
{
  GError *error = NULL;

  if (!signal_handler_init()) {
    printf("Could not set up signal handler");
    return 1;
  }

  /* Create a glib main loop */
  main_loop = g_main_loop_new(NULL, FALSE);

  if(!axoverlay_is_backend_supported(AXOVERLAY_CAIRO_IMAGE_BACKEND)) {
    printf("AXOVERLAY_CAIRO_IMAGE_BACKEND is not supported");
    return 1;
  }

  /* Initialize the library */
  struct axoverlay_settings settings;
  axoverlay_init_axoverlay_settings(&settings);
  settings.render_callback = render_overlay_cb;
  settings.adjustment_callback = NULL;
  settings.select_callback = NULL;
  settings.backend = AXOVERLAY_CAIRO_IMAGE_BACKEND;
  axoverlay_init(&settings, &error);
  if (error != NULL) {
    printf("Failed to initialize axoverlay: %s", error->message);
    g_error_free(error);
    return 1;
  }

  /* Create an overlay */
  struct axoverlay_overlay_data data;
  axoverlay_init_overlay_data(&data);
  data.postype = AXOVERLAY_CUSTOM_NORMALIZED;
  data.anchor_point = AXOVERLAY_ANCHOR_CENTER;
  data.x = 0.0;
  data.y = 0.0;
  data.width = OVERLAY_WIDTH;
  data.height = OVERLAY_WIDTH;
  data.colorspace = AXOVERLAY_COLORSPACE_ARGB32;
  overlay_id = axoverlay_create_overlay(&data, NULL, &error);
  if (error != NULL) {
    printf("Failed to create first overlay: %s", error->message);
    g_error_free(error);
    return 1;
  }

  /* Draw overlays */
  axoverlay_redraw(&error);
  if (error != NULL) {
    printf("Failed to draw overlays: %s", error->message);
    axoverlay_destroy_overlay(overlay_id, &error);
    axoverlay_cleanup();
    g_error_free(error);
    return 1;
  }

  /* Start animation timer */
  animation_timer = g_timeout_add(1000/ANIMATION_FPS, update_overlay_cb, NULL);

  /* Enter main loop */
  g_main_loop_run(main_loop);

  /* Destroy the overlay */
  axoverlay_destroy_overlay(overlay_id, &error);
  if (error != NULL) {
    printf("Failed to destroy first overlay: %s", error->message);
    g_error_free(error);
    return 1;
  }

  /* Release library resources */
  axoverlay_cleanup();

  /* Release the animation timer */
  g_source_remove(animation_timer);

  /* Release main loop */
  g_main_loop_unref(main_loop);

  return 0;
}
