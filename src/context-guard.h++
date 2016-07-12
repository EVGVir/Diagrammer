#pragma once

#include <cairo.h>


/// Saves a cairo context on creation and restores it on destruction.
class ContextGuard {
public:
  /// Saves a cairo context.
  /// @param context Cairo context to be saved.
  explicit ContextGuard(cairo_t *context):
    mContext{context}
  {
    cairo_save(mContext);
  }


  /// Restores the context saved on creation.
  ~ContextGuard() {
    cairo_restore(mContext);
  }

private:
  cairo_t *mContext;            ///< Guarded Cairo context.
};
