using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SpriteMapGenerator
{
    public static class SpritePacker
    {
        public enum PackMode
        {
            Auto,
            GrowDown,
            GrowRight
        }
        public void Pack(ICollection<Sprite> sprites,
                         PackMode mode = PackMode.Auto)
        {
            // sort sprites from largest to smallest
            IOrderedEnumerable<Sprite> sorted =
                (PackMode.GrowDown == mode)
                ? sprites.OrderByDescending(sprite => sprite.Width)
                         .ThenByDescending(sprite => sprite.Height)
                : sprites.OrderByDescending(sprite => sprite.Height)
                         .ThenByDescending(sprite => sprite.Width);
        }
    }
}
