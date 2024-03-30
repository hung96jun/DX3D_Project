struct PixelInput
{
    float4 Position : SV_Position;
    float4 Color : Color;
};

float4 PS(PixelInput Input) : SV_Target
{
    return Input.Color;

}