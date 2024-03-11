struct PixelInput
{
    float4 Position : SV_Position;
};

float4 PS(PixelInput Input) : SV_Target
{
    return float4(1, 0, 0, 1);

}