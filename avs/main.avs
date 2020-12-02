# AVS script for MeGUI 2624

fps = 30

width = 960
height = 720

# c: clip
# dw: destination width
# dh: destination height
# left: crop left
# top: crop top
# right: crop right
# bottom: crop bottom
# color: border color
function TurnRightAmend(clip c, int dw, int dh, int left, int top, int right, int bottom, int color)
{
    sw = c.Width
    sh = c.Height
    right = right <= 0 ? right : -(sw-left-right)
    bottom = bottom <= 0 ? bottom : -(sh-top-bottom)
    c = c.Crop(left, top, right, bottom)
    nw = dw*(sw-left+right)/(dh-top+bottom)
    b = (nw-sh)/2
    c = c.TurnRight().AddBorders(b, 0, b, 0, color)
    return c.LanczosResize(dw, dh)
}

Import("01.avs") \
        ++ Import("02.avs") \
        ++ Import("03.avs") \

LoadPlugin("D:\program\MeGUI\tools\avisynth_plugin\UnDot.dll")

last.UnDot()

__END__
