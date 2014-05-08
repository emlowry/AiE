using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace SpriteMapGenerator
{
    class SheetCanvas : Canvas
    {
        static Pen normalOutline = new Pen(AnimatedPattern.Create(Colors.Lime, Colors.Yellow), 1);
        static Pen selectedOutline = new Pen(AnimatedPattern.Create(Colors.Blue, Colors.Aqua), 1);
        static Pen collidingOutline = new Pen(AnimatedPattern.Create(Colors.Red, Colors.Magenta), 1);
        static Pen controlOutline = new Pen(AnimatedPattern.Create(Colors.Black, Colors.White), 1);

        HashSet<Sprite> selected = new HashSet<Sprite>();
        HashSet<Sprite> colliding = new HashSet<Sprite>();
        HashSet<Sprite> sprites = new HashSet<Sprite>();

        protected override void OnRender(DrawingContext dc)
        {
            foreach (Sprite sprite in sprites)
            {
                dc.DrawImage(sprite.Source, sprite.Boundary);
            }
            foreach (Sprite sprite in sprites)
            {
                if (selected.Contains(sprite))
                {
                    dc.DrawRectangle(null, selectedOutline, sprite.Boundary);
                }
                else if (colliding.Contains(sprite))
                {
                    dc.DrawRectangle(null, collidingOutline, sprite.Boundary);
                }
                else
                {
                    dc.DrawRectangle(null, normalOutline, sprite.Boundary);
                }
            }
        }

        public void AddSprite(Sprite sprite)
        {
            foreach (Sprite otherSprite in sprites)
            {
                if (sprite.IntersectsWith(otherSprite))
                {
                    colliding.Add(sprite);
                    colliding.Add(otherSprite);
                }
            }
            sprites.Add(sprite);
            InvalidateVisual();
        }
    }
}
