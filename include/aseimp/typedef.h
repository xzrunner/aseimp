#pragma once

namespace aseimp
{

enum class NodeClass
{
    // Math Operators
    Saturate,                   // Saturate clamps the input values into the [0,1] range
    Add,                        // Addition of two or more values ( A + B + .. )
    Subtract,                   // Subtraction of two values ( A - B )
    Multiply,                   // Multiplication of two or more values ( A * B * .. )\nIt also handles Matrices multiplication
    Divide,                     // Division of two values ( A / B )
    Remap,                      // Remap value from old min - max range to new min - max range
    Exponential,                // Exponential of scalars and vectors
    Power,                      // Base to the Exp-th power of scalars and vectors
    ScaleAndOffset,             // Scales and offsets an input value\n( ( <b>Value</b> * <b>Scale</b> ) + <b>Offset</b> )
    Lerp,                       // Linear interpolation of two scalars or vectors based on a weight
    Smoothstep,                 // Returns a smooth Hermite interpolation between 0 and 1, if input is in the range [min, max].

    // Logical Operators
    Switch,                     // Creates a shader keyword toggle

    // Functions
    Input,                      // Function Input adds an input port to the shader function
    Output,                     // Function Output adds an output port to the shader function, it's port type is determined automatically.
    Function,                   // Function Node

    // Constants And Properties
    Float,                      // Float property
    Vector2,                    // Vector2 property
    Vector3,                    // Vector3 property
    Vector4,                    // Vector4 property

    // Image Effects
    HSVToRGB,                   // Converts from HSV to RGB color space
    RGBToHSV,                   // Converts from RGB to HSV color space

    // Camera And Screen
    ViewDirection,              // View direction vector, you can select between <b>World</b> space or <b>Tangent</b> space

    // Light
    WorldSpaceLightDir,         // Computes normalized world space light direction
    LightColor,                 // Light Color, RGB value already contains light intensity while A only contains light intensity
    IndirectDiffuseLighting,    // Indirect Lighting
    IndirectSpecularLight,      // Indirect Specular Light

    // Vector Operators
    Normalize,                  // Normalizes a vector
    ChannelMask,                // Mask certain channels from vectors/color components
    DotProduct,                 // Scalar dot product of two vectors ( A . B )
    Combine,                    // Append channels to create a new component

    // Matrix Transform
    ViewMatrix,                 // Current view matrix

    // UV Coordinates
    TexCoords,                  // Texture UV coordinates set, if <b>Tex</b> is connected to a texture object it will use that texture scale factors, otherwise uses <b>Tilling</b> and <b>Offset</b> port values

    // Textures
    Tex2DAsset,                 // Represents a Texture Asset. Can be used in samplers <b>Tex</b> inputs or shader function inputs to reuse the same texture multiple times.
    SampleTex2D,
    TextureTransform,           // Gives access to texture tiling and offset as set on the material inspector

    // Surface Data
    WorldNormalVector,          // Per pixel world normal vector, accepts a <b>Normal</b> vector in tangent space (ie: normalmap)

    // Miscellaneous
    SetReference,               // Forces a local variable to be written with the given name. Can then be fetched at any place with a <b>Get Local Var</b> node.
    GetReference,               // Use a registered local variable
    CustomExpression,           // Creates a custom expression or function if <b>return</b> is detected in the written code.

    // Tools
    Commentary,                 // Commentary

    // Master
    StandardSurfaceOutput,      // Surface shader generator output
};

// MasterNode
enum class PrecisionType
{
    Float = 0,
    Half,
    Fixed
};

// PropertyNode
enum class PropertyType
{
    Constant = 0,
    Property,
    InstancedProperty,
    Global
};

// PropertyNode
enum class VariableMode
{
    Create,
    Fetch
};

// ViewDirInputsCoordNode
enum class ViewSpace
{
    Tangent,
    World
};

// TexturePropertyNode
enum class TexturePropertyValues
{
    white,
    black,
    gray,
    bump
};

// TexturePropertyNode
enum class TextureType
{
    Texture1D,
    Texture2D,
    Texture3D,
    Cube,
    Texture2DArray,
    ProceduralTexture
};

// TexturePropertyNode
enum class AutoCastType
{
    Auto = 0,
    LockedToTexture1D,
    LockedToTexture2D,
    LockedToTexture3D,
    LockedToCube,
    LockedToTexture2DArray
};

// SamplerNode
enum class TexReferenceType
{
    Object = 0,
    Instance
};

// SamplerNode
enum class MipType
{
    Auto,
    MipLevel,
    MipBias,
    Derivative
};

// SamplerNode
enum class ReferenceState
{
    Self,
    Connected,
    Instance
};

// WirePort
enum class WirePortDataType
{
    OBJECT = 1 << 1,
    FLOAT = 1 << 2,
    FLOAT2 = 1 << 3,
    FLOAT3 = 1 << 4,
    FLOAT4 = 1 << 5,
    FLOAT3x3 = 1 << 6,
    FLOAT4x4 = 1 << 7,
    COLOR = 1 << 8,
    INT = 1 << 9,
    SAMPLER1D = 1 << 10,
    SAMPLER2D = 1 << 11,
    SAMPLER3D = 1 << 12,
    SAMPLERCUBE = 1 << 13,
    UINT = 1 << 14
};

// WirePort
enum class VariableQualifiers
{
    In = 0,
    Out,
    InOut
};

// StaticSwitch
enum class KeywordModeType
{
    Toggle = 0,
    ToggleOff,
    KeywordEnum
};

// StandardSurfaceOutputNode
enum class VertexMode
{
    Relative,
    Absolute
};

// StandardSurfaceOutputNode
enum class RenderPath
{
    All,
    ForwardOnly,
    DeferredOnly
};

// StandardSurfaceOutputNode
enum class StandardShaderLightModel
{
    Standard,
    StandardSpecular,
    Lambert,
    BlinnPhong,
    Unlit,
    CustomLighting
};

// StandardSurfaceOutputNode
enum class CullMode
{
    Back,
    Front,
    Off
};

// StandardSurfaceOutputNode
enum class AlphaMode
{
    Opaque = 0,
    Masked = 1,
    Transparent = 2, // Transparent (alpha:fade)
    Translucent = 3,
    Premultiply = 4, // Alpha Premul (alpha:premul)
    Custom = 5,
};

// StandardSurfaceOutputNode
enum class RenderType
{
    Opaque,
    Transparent,
    TransparentCutout,
    Background,
    Overlay,
    TreeOpaque,
    TreeTransparentCutout,
    TreeBillboard,
    Grass,
    GrassBillboard,
    Custom
};

// StandardSurfaceOutputNode
enum class RenderQueue
{
    Background,
    Geometry,
    AlphaTest,
    Transparent,
    Overlay
};

// StandardSurfaceOutputNode
enum class RenderPlatforms
{
    d3d9,
    d3d11,
    glcore,
    gles,
    gles3,
    metal,
    d3d11_9x,
    xbox360,
    xboxone,
    ps4,
    psp2,
    n3ds,
    wiiu
};

// RenderingOptionsOpHelper
enum class DisableBatchingTagValues
{
    True,
    False,
    LODFading
};

// BlendOpsHelper
enum class AvailableBlendFactor
{
	One = 1,
	Zero = 0,
	SrcColor = 3,
	SrcAlpha = 5,
	DstColor = 2,
	DstAlpha = 7,
	OneMinusSrcColor = 6,
	OneMinusSrcAlpha = 10,
	OneMinusDstColor = 4,
	OneMinusDstAlpha = 8,
	SrcAlphaSaturate = 9
};

// BlendOpsHelper
enum class AvailableBlendOps
{
	OFF = 0,
	Add,
	Sub,
	RevSub,
	Min,
	Max,
	//Direct X11 only
	LogicalClear,
	LogicalSet,
	LogicalCopy,
	LogicalCopyInverted,
	LogicalNoop,
	LogicalInvert,
	LogicalAnd,
	LogicalNand,
	LogicalOr,
	LogicalNor,
	LogicalXor,
	LogicalEquiv,
	LogicalAndReverse,
	LogicalAndInverted,
	LogicalOrReverse,
	LogicalOrInverted
};

// OutlineOpHelper
enum class OutlineMode
{
    VertexOffset,
    VertexScale
};

// BillboardOpHelper
enum class BillboardType
{
    Cylindrical,
    Spherical
};

// TemplateAdditionalDirectivesHelper
enum class AdditionalLineType
{
    Include,
    Define,
    Pragma,
    Custom
};

void regist_rttr_typedef();

}