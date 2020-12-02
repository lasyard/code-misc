# AVS script for MeGUI 2624

file = "D:\video\160106_202000.mov"

LoadPlugin("D:\program\MeGUI\tools\lsmash\LSMASHSource.dll")

v = LSMASHVideoSource(file).AssumeFPS(fps)

# hue
# Adjust the color hue of the image. Positive values shift the image towards red. Negative values shift it towards green. (-180.0 to +180.0, default 0.0)
# sat
# Adjust the color saturation of the image. Values above 1.0 increase the saturation. Values below 1.0 reduce the saturation. Use sat=0 to convert to GreyScale. (0.0 to 10.0, default 1.0)
# bright
# Change the brightness of the image. Positive values increase the brightness (the clip gets brighter). Negative values decrease the brightness (the clip gets darker). If the clip is too dark or too bright you can use this setting to correct it. (-255.0 to 255.0, default 0.0)
# cont
# Change the contrast of the image. Values above 1.0 increase the contrast (the luma range will be stretched). Values below 1.0 decrease the contrast (the luma range will be contracted). If details can't be seen in dark or bright areas, you can increase the contrast to make those details more visible. (0.0 to 10.0, default 1.0)
v = v.Tweak(hue = 0.0, sat = 1.2, bright = 15.0, cont = 1.5)

a = LSMASHAudioSource(file)

AudioDub(a, v)

c1 = last.Trim(0, 633).ConvertToRGB(matrix = "Rec709").Animate(0, 633, "TurnRightAmend",
        \ width, height, 640, 0, -470, 0, $000000,
        \ width, height, 0, 0, 0, 0, $000000
        \ ).ConvertToYV12().FadeIO0(fps/2)

c2 = last.Trim(1078, 1385).Crop(160, 0, 0, 0).LanczosResize(width, height).FadeIO0(fps/2)

c1 ++ c2
