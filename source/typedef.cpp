#include "aseimp/typedef.h"

#include <rttr/registration.h>

RTTR_REGISTRATION
{

rttr::registration::enumeration<aseimp::NodeClass>("aseimp::NodeClass")
(
    // Math Operators
	rttr::value("SaturateNode",                 aseimp::NodeClass::Saturate),
    rttr::value("SimpleAddOpNode",              aseimp::NodeClass::Add),
    rttr::value("SimpleSubtractOpNode",         aseimp::NodeClass::Subtract),
    rttr::value("SimpleMultiplyOpNode",         aseimp::NodeClass::Multiply),
    rttr::value("SimpleDivideOpNode",           aseimp::NodeClass::Divide),
    rttr::value("TFHCRemapNode",                aseimp::NodeClass::Remap),
    rttr::value("Exp2OpNode",                   aseimp::NodeClass::Exponential),
    rttr::value("PowerNode",                    aseimp::NodeClass::Power),
    rttr::value("ScaleAndOffsetNode",           aseimp::NodeClass::ScaleAndOffset),
    rttr::value("LerpOp",                       aseimp::NodeClass::Lerp),
    rttr::value("SmoothstepOpNode",             aseimp::NodeClass::Smoothstep),
    // Logical Operators
    rttr::value("StaticSwitch",                 aseimp::NodeClass::Switch),
    // Functions
    rttr::value("FunctionInput",                aseimp::NodeClass::Input),
    rttr::value("FunctionOutput",               aseimp::NodeClass::Output),
    rttr::value("FunctionNode",                 aseimp::NodeClass::Function),
    // Constants And Properties
    rttr::value("RangedFloatNode",              aseimp::NodeClass::Float),
    rttr::value("Vector2Node",                  aseimp::NodeClass::Vector2),
    rttr::value("Vector3Node",                  aseimp::NodeClass::Vector3),
    rttr::value("Vector4Node",                  aseimp::NodeClass::Vector4),
    // Image Effects
    rttr::value("HSVToRGBNode",                 aseimp::NodeClass::HSVToRGB),
    rttr::value("RGBToHSVNode",                 aseimp::NodeClass::RGBToHSV),
    // Camera And Screen
    rttr::value("ViewDirInputsCoordNode",       aseimp::NodeClass::ViewDirection),
    // Light
    rttr::value("WorldSpaceLightDirHlpNode",    aseimp::NodeClass::WorldSpaceLightDir),
    rttr::value("LightColorNode",               aseimp::NodeClass::LightColor),
    rttr::value("IndirectDiffuseLighting",      aseimp::NodeClass::IndirectDiffuseLighting),
    rttr::value("IndirectSpecularLight",        aseimp::NodeClass::IndirectSpecularLight),
    // Vector Operators
    rttr::value("NormalizeNode",                aseimp::NodeClass::Normalize),
    rttr::value("ComponentMaskNode",            aseimp::NodeClass::ChannelMask),
    rttr::value("DotProductOpNode",             aseimp::NodeClass::DotProduct),
    rttr::value("DynamicAppendNode",            aseimp::NodeClass::Combine),
    // Matrix Transform
    rttr::value("ViewMatrixNode",               aseimp::NodeClass::ViewMatrix),
    // UV Coordinates
    rttr::value("TextureCoordinatesNode",       aseimp::NodeClass::TexCoords),
    // Textures
    rttr::value("TexturePropertyNode",          aseimp::NodeClass::Tex2DAsset),
    rttr::value("SamplerNode",                  aseimp::NodeClass::SampleTex2D),
    rttr::value("TextureTransformNode",         aseimp::NodeClass::TextureTransform),
    // Surface Data
    rttr::value("WorldNormalVector",            aseimp::NodeClass::WorldNormalVector),
    // Miscellaneous
    rttr::value("RegisterLocalVarNode",         aseimp::NodeClass::SetReference),
    rttr::value("GetLocalVarNode",              aseimp::NodeClass::GetReference),
    rttr::value("CustomExpressionNode",         aseimp::NodeClass::CustomExpression),
    // Tools
    rttr::value("CommentaryNode",               aseimp::NodeClass::Commentary),
    // Master
    rttr::value("StandardSurfaceOutputNode",    aseimp::NodeClass::StandardSurfaceOutput)
);

rttr::registration::enumeration<aseimp::PrecisionType>("aseimp::PrecisionType")
(
	rttr::value("Float", aseimp::PrecisionType::Float),
    rttr::value("Half",  aseimp::PrecisionType::Half),
    rttr::value("Fixed", aseimp::PrecisionType::Fixed)
);

rttr::registration::enumeration<aseimp::PropertyType>("aseimp::PropertyType")
(
	rttr::value("Constant",          aseimp::PropertyType::Constant),
    rttr::value("Property",          aseimp::PropertyType::Property),
    rttr::value("InstancedProperty", aseimp::PropertyType::InstancedProperty),
    rttr::value("Global",            aseimp::PropertyType::Global)
);

rttr::registration::enumeration<aseimp::VariableMode>("aseimp::VariableMode")
(
	rttr::value("Create", aseimp::VariableMode::Create),
    rttr::value("Fetch",  aseimp::VariableMode::Fetch)
);

rttr::registration::enumeration<aseimp::ViewSpace>("aseimp::ViewSpace")
(
	rttr::value("Tangent", aseimp::ViewSpace::Tangent),
    rttr::value("World",   aseimp::ViewSpace::World)
);

rttr::registration::enumeration<aseimp::TexturePropertyValues>("aseimp::TexturePropertyValues")
(
	rttr::value("white", aseimp::TexturePropertyValues::white),
    rttr::value("black", aseimp::TexturePropertyValues::black),
    rttr::value("gray",  aseimp::TexturePropertyValues::gray),
    rttr::value("bump",  aseimp::TexturePropertyValues::bump)
);

rttr::registration::enumeration<aseimp::TextureType>("aseimp::TextureType")
(
	rttr::value("Texture1D",         aseimp::TextureType::Texture1D),
    rttr::value("Texture2D",         aseimp::TextureType::Texture2D),
    rttr::value("Texture3D",         aseimp::TextureType::Texture3D),
    rttr::value("Cube",              aseimp::TextureType::Cube),
    rttr::value("Texture2DArray",    aseimp::TextureType::Texture2DArray),
    rttr::value("ProceduralTexture", aseimp::TextureType::ProceduralTexture)
);

rttr::registration::enumeration<aseimp::AutoCastType>("aseimp::AutoCastType")
(
	rttr::value("Auto",                   aseimp::AutoCastType::Auto),
    rttr::value("LockedToTexture1D",      aseimp::AutoCastType::LockedToTexture1D),
    rttr::value("LockedToTexture2D",      aseimp::AutoCastType::LockedToTexture2D),
    rttr::value("LockedToTexture3D",      aseimp::AutoCastType::LockedToTexture3D),
    rttr::value("LockedToCube",           aseimp::AutoCastType::LockedToCube),
    rttr::value("LockedToTexture2DArray", aseimp::AutoCastType::LockedToTexture2DArray)
);

rttr::registration::enumeration<aseimp::TexReferenceType>("aseimp::TexReferenceType")
(
	rttr::value("Object",   aseimp::TexReferenceType::Object),
    rttr::value("Instance", aseimp::TexReferenceType::Instance)
);

rttr::registration::enumeration<aseimp::MipType>("aseimp::MipType")
(
	rttr::value("Auto",       aseimp::MipType::Auto),
    rttr::value("MipLevel",   aseimp::MipType::MipLevel),
    rttr::value("MipBias",    aseimp::MipType::MipBias),
    rttr::value("Derivative", aseimp::MipType::Derivative)
);

rttr::registration::enumeration<aseimp::ReferenceState>("aseimp::ReferenceState")
(
	rttr::value("Self",      aseimp::ReferenceState::Self),
    rttr::value("Connected", aseimp::ReferenceState::Connected),
    rttr::value("Instance",  aseimp::ReferenceState::Instance)
);

rttr::registration::enumeration<aseimp::WirePortDataType>("aseimp::WirePortDataType")
(
	rttr::value("OBJECT",      aseimp::WirePortDataType::OBJECT),
    rttr::value("FLOAT",       aseimp::WirePortDataType::FLOAT),
    rttr::value("FLOAT2",      aseimp::WirePortDataType::FLOAT2),
    rttr::value("FLOAT3",      aseimp::WirePortDataType::FLOAT3),
    rttr::value("FLOAT4",      aseimp::WirePortDataType::FLOAT4),
    rttr::value("FLOAT3x3",    aseimp::WirePortDataType::FLOAT3x3),
    rttr::value("FLOAT4x4",    aseimp::WirePortDataType::FLOAT4x4),
    rttr::value("COLOR",       aseimp::WirePortDataType::COLOR),
    rttr::value("INT",         aseimp::WirePortDataType::INT),
    rttr::value("SAMPLER1D",   aseimp::WirePortDataType::SAMPLER1D),
    rttr::value("SAMPLER2D",   aseimp::WirePortDataType::SAMPLER2D),
    rttr::value("SAMPLER3D",   aseimp::WirePortDataType::SAMPLER3D),
    rttr::value("SAMPLERCUBE", aseimp::WirePortDataType::SAMPLERCUBE),
    rttr::value("UINT",        aseimp::WirePortDataType::UINT)
);

rttr::registration::enumeration<aseimp::VariableQualifiers>("aseimp::VariableQualifiers")
(
	rttr::value("In",    aseimp::VariableQualifiers::In),
    rttr::value("Out",   aseimp::VariableQualifiers::Out),
    rttr::value("InOut", aseimp::VariableQualifiers::InOut)
);

rttr::registration::enumeration<aseimp::KeywordModeType>("aseimp::KeywordModeType")
(
	rttr::value("Toggle",      aseimp::KeywordModeType::Toggle),
    rttr::value("ToggleOff",   aseimp::KeywordModeType::ToggleOff),
    rttr::value("KeywordEnum", aseimp::KeywordModeType::KeywordEnum)
);

rttr::registration::enumeration<aseimp::VertexMode>("aseimp::VertexMode")
(
	rttr::value("Relative", aseimp::VertexMode::Relative),
    rttr::value("Absolute", aseimp::VertexMode::Absolute)
);

rttr::registration::enumeration<aseimp::RenderPath>("aseimp::RenderPath")
(
	rttr::value("All",          aseimp::RenderPath::All),
    rttr::value("ForwardOnly",  aseimp::RenderPath::ForwardOnly),
    rttr::value("DeferredOnly", aseimp::RenderPath::DeferredOnly)
);

rttr::registration::enumeration<aseimp::StandardShaderLightModel>("aseimp::StandardShaderLightModel")
(
	rttr::value("Standard",         aseimp::StandardShaderLightModel::Standard),
    rttr::value("StandardSpecular", aseimp::StandardShaderLightModel::StandardSpecular),
    rttr::value("Lambert",          aseimp::StandardShaderLightModel::Lambert),
    rttr::value("BlinnPhong",       aseimp::StandardShaderLightModel::BlinnPhong),
    rttr::value("Unlit",            aseimp::StandardShaderLightModel::Unlit),
    rttr::value("CustomLighting",   aseimp::StandardShaderLightModel::CustomLighting)
);

rttr::registration::enumeration<aseimp::CullMode>("aseimp::CullMode")
(
	rttr::value("Back",  aseimp::CullMode::Back),
    rttr::value("Front", aseimp::CullMode::Front),
    rttr::value("Off",   aseimp::CullMode::Off)
);

rttr::registration::enumeration<aseimp::AlphaMode>("aseimp::AlphaMode")
(
	rttr::value("Opaque",      aseimp::AlphaMode::Opaque),
    rttr::value("Masked",      aseimp::AlphaMode::Masked),
    rttr::value("Transparent", aseimp::AlphaMode::Transparent),
    rttr::value("Translucent", aseimp::AlphaMode::Translucent),
    rttr::value("Premultiply", aseimp::AlphaMode::Premultiply),
    rttr::value("Custom",      aseimp::AlphaMode::Custom)
);

rttr::registration::enumeration<aseimp::RenderType>("aseimp::RenderType")
(
	rttr::value("Opaque",                aseimp::RenderType::Opaque),
    rttr::value("Transparent",           aseimp::RenderType::Transparent),
    rttr::value("TransparentCutout",     aseimp::RenderType::TransparentCutout),
    rttr::value("Background",            aseimp::RenderType::Background),
    rttr::value("Overlay",               aseimp::RenderType::Overlay),
    rttr::value("TreeOpaque",            aseimp::RenderType::TreeOpaque),
    rttr::value("TreeTransparentCutout", aseimp::RenderType::TreeTransparentCutout),
    rttr::value("TreeBillboard",         aseimp::RenderType::TreeBillboard),
    rttr::value("Grass",                 aseimp::RenderType::Grass),
    rttr::value("GrassBillboard",        aseimp::RenderType::GrassBillboard),
    rttr::value("Custom",                aseimp::RenderType::Custom)
);

rttr::registration::enumeration<aseimp::RenderQueue>("aseimp::RenderQueue")
(
	rttr::value("Background",  aseimp::RenderQueue::Background),
    rttr::value("Geometry",    aseimp::RenderQueue::Geometry),
    rttr::value("AlphaTest",   aseimp::RenderQueue::AlphaTest),
    rttr::value("Transparent", aseimp::RenderQueue::Transparent),
    rttr::value("Overlay",     aseimp::RenderQueue::Overlay)
);

rttr::registration::enumeration<aseimp::DisableBatchingTagValues>("aseimp::DisableBatchingTagValues")
(
	rttr::value("True",      aseimp::DisableBatchingTagValues::True),
    rttr::value("False",     aseimp::DisableBatchingTagValues::False),
    rttr::value("LODFading", aseimp::DisableBatchingTagValues::LODFading)
);

rttr::registration::enumeration<aseimp::AvailableBlendFactor>("aseimp::AvailableBlendFactor")
(
	rttr::value("One",              aseimp::AvailableBlendFactor::One),
    rttr::value("Zero",             aseimp::AvailableBlendFactor::Zero),
    rttr::value("SrcColor",         aseimp::AvailableBlendFactor::SrcColor),
    rttr::value("SrcAlpha",         aseimp::AvailableBlendFactor::SrcAlpha),
    rttr::value("DstColor",         aseimp::AvailableBlendFactor::DstColor),
    rttr::value("DstAlpha",         aseimp::AvailableBlendFactor::DstAlpha),
    rttr::value("OneMinusSrcColor", aseimp::AvailableBlendFactor::OneMinusSrcColor),
    rttr::value("OneMinusSrcAlpha", aseimp::AvailableBlendFactor::OneMinusSrcAlpha),
    rttr::value("OneMinusDstColor", aseimp::AvailableBlendFactor::OneMinusDstColor),
    rttr::value("OneMinusDstAlpha", aseimp::AvailableBlendFactor::OneMinusDstAlpha),
    rttr::value("SrcAlphaSaturate", aseimp::AvailableBlendFactor::SrcAlphaSaturate)
);

rttr::registration::enumeration<aseimp::AvailableBlendOps>("aseimp::AvailableBlendOps")
(
	rttr::value("OFF",                 aseimp::AvailableBlendOps::OFF),
    rttr::value("Add",                 aseimp::AvailableBlendOps::Add),
    rttr::value("Sub",                 aseimp::AvailableBlendOps::Sub),
    rttr::value("RevSub",              aseimp::AvailableBlendOps::RevSub),
    rttr::value("Min",                 aseimp::AvailableBlendOps::Min),
    rttr::value("Max",                 aseimp::AvailableBlendOps::Max),
    rttr::value("LogicalClear",        aseimp::AvailableBlendOps::LogicalClear),
    rttr::value("LogicalSet",          aseimp::AvailableBlendOps::LogicalSet),
    rttr::value("LogicalCopy",         aseimp::AvailableBlendOps::LogicalCopy),
    rttr::value("LogicalCopyInverted", aseimp::AvailableBlendOps::LogicalCopyInverted),
    rttr::value("LogicalNoop",         aseimp::AvailableBlendOps::LogicalNoop),
    rttr::value("LogicalInvert",       aseimp::AvailableBlendOps::LogicalInvert),
    rttr::value("LogicalAnd",          aseimp::AvailableBlendOps::LogicalAnd),
    rttr::value("LogicalNand",         aseimp::AvailableBlendOps::LogicalNand),
    rttr::value("LogicalOr",           aseimp::AvailableBlendOps::LogicalOr),
    rttr::value("LogicalNor",          aseimp::AvailableBlendOps::LogicalNor),
    rttr::value("LogicalXor",          aseimp::AvailableBlendOps::LogicalXor),
    rttr::value("LogicalEquiv",        aseimp::AvailableBlendOps::LogicalEquiv),
    rttr::value("LogicalAndReverse",   aseimp::AvailableBlendOps::LogicalAndReverse),
    rttr::value("LogicalAndInverted",  aseimp::AvailableBlendOps::LogicalAndInverted),
    rttr::value("LogicalOrReverse",    aseimp::AvailableBlendOps::LogicalOrReverse),
    rttr::value("LogicalOrInverted",   aseimp::AvailableBlendOps::LogicalOrInverted)
);

rttr::registration::enumeration<aseimp::OutlineMode>("aseimp::OutlineMode")
(
	rttr::value("VertexOffset", aseimp::OutlineMode::VertexOffset),
    rttr::value("VertexScale",  aseimp::OutlineMode::VertexScale)
);

rttr::registration::enumeration<aseimp::BillboardType>("aseimp::BillboardType")
(
	rttr::value("Cylindrical", aseimp::BillboardType::Cylindrical),
    rttr::value("Spherical",   aseimp::BillboardType::Spherical)
);

rttr::registration::enumeration<aseimp::AdditionalLineType>("aseimp::AdditionalLineType")
(
	rttr::value("Include", aseimp::AdditionalLineType::Include),
    rttr::value("Define",  aseimp::AdditionalLineType::Define),
    rttr::value("Pragma",  aseimp::AdditionalLineType::Pragma),
    rttr::value("Custom",  aseimp::AdditionalLineType::Custom)
);

}

namespace aseimp
{

void regist_rttr_typedef()
{
}

}