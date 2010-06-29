#ifndef OSMSCOUT_MAP_MAPPAINTERCAIRO_H
#define OSMSCOUT_MAP_MAPPAINTERCAIRO_H

/*
  This source is part of the libosmscout-map library
  Copyright (C) 2009  Tim Teulings

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*/

#include <set>

#if defined(__WIN32__) || defined(WIN32) || defined(__APPLE__)
  #include <cairo.h>
#else
  #include <cairo/cairo.h>
#endif

#include <osmscout/Private/MapImportExport.h>

#include <osmscout/MapPainter.h>

namespace osmscout {

  class OSMSCOUT_MAP_API MapPainterCairo : public MapPainter
  {
  private:
    cairo_t                               *draw;    //! The cairo cairo_t to draw into
    std::vector<cairo_surface_t*>         images;   //! vector of cairo surfaces for images and patterns
    std::vector<cairo_pattern_t*>         patterns; //! cairo pattern structure for patterns
    std::map<size_t,cairo_scaled_font_t*> font;     //! Cached scaled font

  private:
    cairo_scaled_font_t* GetScaledFont(cairo_t* draw,
                                       size_t fontSize);

    bool HasIcon(const StyleConfig& styleConfig,
                 IconStyle& style);
                 
    bool HasPattern(const StyleConfig& styleConfig,
                   PatternStyle& style);

    void ClearArea(const StyleConfig& styleConfig,
                   const Projection& projection,
                   const MapParameter& parameter,
                   const MapData& data);

    void DrawLabel(const Projection& projection,
                   const LabelStyle& style,
                   const std::string& text,
                   double x, double y);

    void DrawContourLabel(const Projection& projection,
                          const LabelStyle& style,
                          const std::string& text,
                          const std::vector<Point>& nodes);

    void DrawSymbol(const SymbolStyle* style,
                    double x, double y);

    void DrawIcon(const IconStyle* style,
                  double x, double y);

    void DrawPath(LineStyle::Style style,
                  const Projection& projection,
                  double r, double g, double b, double a,
                  double width,
                  const std::vector<Point>& nodes);

    void FillRegion(const std::vector<Point>& nodes,
                    const Projection& projection,
                    const FillStyle& style);

    void FillRegion(const std::vector<Point>& nodes,
                    const Projection& projection,
                    PatternStyle& style);
                 
    void DrawWayOutline(const StyleConfig& styleConfig,
                        const Projection& projection,
                        TypeId type,
                        const SegmentAttributes& attributes,
                        const std::vector<Point>& nodes);

    void DrawArea(const StyleConfig& styleConfig,
                  const Projection& projection,
                  TypeId type,
                  int layer,
                  const SegmentAttributes& attributes,
                  const std::vector<Point>& nodes);
                                           
  public:
    MapPainterCairo();
    ~MapPainterCairo();


    bool DrawMap(const StyleConfig& styleConfig,
                 const Projection& projection,
                 const MapParameter& parameter,
                 const MapData& data,
                 cairo_t *draw);
  };
}

#endif