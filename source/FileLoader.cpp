#include "aseimp/FileLoader.h"
#include "aseimp/ImportStream.h"

#include <yaml-cpp/yaml.h>

#include <assert.h>

#include <fstream>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include <rttr/enumeration.h>

#define ENUM_PARSE(type_str, type_name) rttr::type::get_by_name("aseimp::"#type_name).get_enumeration().name_to_value(type_str).get_value<aseimp::type_name>()

namespace aseimp
{

void FileLoader::LoadAsset(const std::string& filepath)
{
    if (!boost::filesystem::exists(filepath)) {
        return;
    }

    auto root = YAML::LoadFile(filepath);

    auto mono = root["MonoBehaviour"];
    assert(!mono.IsNull());

    auto name = mono["m_Name"].as<std::string>();
    auto func = mono["m_functionInfo"].as<std::string>();

    std::stringstream ss(func);
    LoadASE(ss);
}

void FileLoader::LoadShader(const std::string& filepath)
{
    std::locale::global(std::locale(""));
    std::ifstream fin(filepath);
    std::locale::global(std::locale("C"));

    LoadASE(fin);

    fin.close();
}

void FileLoader::LoadASE(std::istream& is)
{
    std::string line;

    while (std::getline(is, line))
    {
        if (line.find("ASEBEGIN") != std::string::npos) {
            break;
        }
    }

    // version
    std::getline(is, line);
    m_version = std::atoi(line.substr(strlen("Version=")).c_str());

    // camera
    // x, y, w, h, offx, offy, zoom, NodeParametersWindowMaximized, PaletteWindowMaximized
    std::getline(is, line);

    while (std::getline(is, line))
    {
        if (line.find("ASEEND") != std::string::npos) {
            break;
        }

        ImportStream is(line);
        auto type = is.String();
        if (type == "Node") {
            LoadNode(is);
        } else if (type == "WireConnection") {
            LoadConn(is);
        }
    }
}

void FileLoader::LoadNode(ImportStream& is)
{
    Node node;

    std::string name = is.String();
    name = name.substr(strlen("AmplifyShaderEditor."));
    node.cls = ENUM_PARSE(name, NodeClass);

    // ParentNode::ReadFromString
    node.uid = is.Int32();

    std::vector<float> pos;
    StringToMultiFloat(is.String(), pos);
    assert(pos.size() == 2);
    node.x = pos[0];
    node.y = pos[1];

    if (m_version > 22) {
        auto precision_type = ENUM_PARSE(is.String(), PrecisionType);
    }
    if (m_version > 5004) {
        bool show_preview = is.Bool();
    }

    switch (node.cls)
    {
    case NodeClass::Add:
        LoadDynamicTypeNode(is);
        break;
    case NodeClass::Subtract:
        LoadDynamicTypeNode(is);
        break;
    case NodeClass::Multiply:
        LoadDynamicTypeNode(is);
        break;
    case NodeClass::Divide:
        LoadDynamicTypeNode(is);
        break;
    case NodeClass::Input:
    {
        std::string input_name = is.String();
        int         selected_input_type_int = is.Int32();
        int         order_index = is.Int32();
        bool        auto_cast = is.Bool();

        node.vars.insert({ "name", Variant(input_name) });
    }
        break;
    case NodeClass::Output:
    {
        // OutputNode
        bool is_main_output_node = is.Bool();

        // FunctionOutput
        std::string output_name = is.String();
        int         order_index = is.Int32();
        if (m_version > 13706) {
            bool preview_node = is.Bool();
        }

        node.vars.insert({ "name", Variant(output_name) });
    }
        break;
    case NodeClass::Float:
    {
        PropertyNode prop;
        prop.Load(m_version, is);

        float default_val = is.Float();
        if (m_version > 14101) {
            float material_val = is.Float();
        }
        float min_val = is.Float();
        float max_val = is.Float();

        node.vars.insert({ "name", Variant(prop.name) });
        node.vars.insert({ "x", Variant(default_val) });
    }
        break;
    case NodeClass::Vector2:
    {
        PropertyNode prop;
        prop.Load(m_version, is);

        std::vector<float> default_value;
        StringToMultiFloat(is.String(), default_value);
        assert(default_value.size() == 2);
        if (m_version > 14101) {
            std::vector<float> material_value;
            StringToMultiFloat(is.String(), material_value);
            assert(material_value.size() == 2);
        }

        node.vars.insert({ "name", Variant(prop.name) });
        node.vars.insert({ "x", Variant(default_value[0]) });
        node.vars.insert({ "y", Variant(default_value[1]) });
    }
        break;
    case NodeClass::Vector3:
    {
        PropertyNode prop;
        prop.Load(m_version, is);

        std::vector<float> default_value;
        StringToMultiFloat(is.String(), default_value);
        assert(default_value.size() == 3);
        if (m_version > 14101) {
            std::vector<float> material_value;
            StringToMultiFloat(is.String(), material_value);
            assert(material_value.size() == 3);
        }

        node.vars.insert({ "name", Variant(prop.name) });
        node.vars.insert({ "x", Variant(default_value[0]) });
        node.vars.insert({ "y", Variant(default_value[1]) });
        node.vars.insert({ "z", Variant(default_value[2]) });
    }
        break;
    case NodeClass::Vector4:
    {
        PropertyNode prop;
        prop.Load(m_version, is);

        std::vector<float> default_value;
        StringToMultiFloat(is.String(), default_value);
        assert(default_value.size() == 4);
        if (m_version > 14101) {
            std::vector<float> material_value;
            StringToMultiFloat(is.String(), material_value);
            assert(material_value.size() == 4);
        }

        node.vars.insert({ "name", Variant(prop.name) });
        node.vars.insert({ "x", Variant(default_value[0]) });
        node.vars.insert({ "y", Variant(default_value[1]) });
        node.vars.insert({ "z", Variant(default_value[2]) });
        node.vars.insert({ "w", Variant(default_value[3]) });
    }
        break;
    case NodeClass::ViewDirection:
        if (m_version > 2402) {
            auto view_dir_space = ENUM_PARSE(is.String(), ViewSpace);
            node.vars.insert({ "view_dir_space", Variant(static_cast<int>(view_dir_space)) });
        }
        if (m_version > 15201) {
            bool safe_normalize = is.Bool();
            node.vars.insert({ "safe_normalize", Variant(safe_normalize) });
        }
        break;
    case NodeClass::WorldSpaceLightDir:
        if (m_version > 15201) {
            bool safe_normalize = is.Bool();
        }
        break;
    case NodeClass::SampleTex2D:
    {
        PropertyNode prop;
        prop.Load(m_version, is);

        std::string default_tex_guid = is.String();
        if (m_version > 14101) {
            std::string material_tex_guid = is.String();
        }
        bool use_semantics = is.Bool();
        int  texcoord_set  = is.Int32();
        bool is_normal_map = is.Bool();
        auto default_tex_val = ENUM_PARSE(is.String(), TexturePropertyValues);
        auto auto_cast_mode = ENUM_PARSE(is.String(), AutoCastType);
        bool auto_unpack_normals = is.Bool();
        if (m_version > 12)
        {
            auto reference_type = ENUM_PARSE(is.String(), TexReferenceType);
            if (m_version > 22) {
                int ref_node_id = is.Int32();
            } else {
                int ref_array_id = is.Int32();
            }
        }
        if (m_version > 2406) {
            auto mip_mode = ENUM_PARSE(is.String(), MipType);
        }
        if (m_version > 3201) {
            auto current_type = ENUM_PARSE(is.String(), TextureType);
        }
    }
        break;
    case NodeClass::ChannelMask:
    {
        bool rgba[4];
        for (int i = 0; i < 4; ++i) {
            rgba[i] = is.Bool();
        }
        node.vars.insert({ "r", Variant(rgba[0]) });
        node.vars.insert({ "g", Variant(rgba[1]) });
        node.vars.insert({ "b", Variant(rgba[2]) });
        node.vars.insert({ "a", Variant(rgba[3]) });
    }
        break;
    case NodeClass::Commentary:
    {
        const float width  = is.Float();
        const float height = is.Float();

        auto comment_text = is.String();

        std::vector<int> children;
        int child_n = is.Int32();
        children.reserve(child_n);
        for (int i = 0; i < child_n; ++i) {
            children.push_back(is.Int32());
        }

        if (m_version > 5004) {
            std::string title_text = is.String();
        }

        if (m_version > 12002)
        {
            auto& color_channels_str = is.String();
            std::vector<std::string> sub_tokens;
            boost::split(sub_tokens, color_channels_str, boost::is_any_of(","));
            assert(sub_tokens.size() == 4);

            int r = std::atoi(sub_tokens[0].c_str());
            int g = std::atoi(sub_tokens[1].c_str());
            int b = std::atoi(sub_tokens[2].c_str());
            int a = std::atoi(sub_tokens[3].c_str());
        }

        node.vars.insert({ "width",  Variant(width) });
        node.vars.insert({ "height", Variant(height) });
        node.vars.insert({ "text",   Variant(comment_text) });
    }
        break;
    case NodeClass::WorldNormalVector:
        if (m_version > 14202) {
            bool normalize = is.Bool();
        }
        break;
    case NodeClass::SetLocalVar:
    {
        auto& var_name = is.String();

        if (m_version > 14) {
            int order_index = is.Int32();
        }

        bool auto_index_active = false;
        if (m_version > 3106) {
            auto_index_active = is.Bool();
        }

        node.vars.insert({ "name", Variant(var_name) });
    }
        break;
    case NodeClass::GetLocalVar:
    {
        if (m_version > 15) {
            int node_id = is.Int32();
            if (m_version > 15500) {
                std::string var_name = is.String();
            }
        } else {
            int reference_id = is.Int32();
        }
    }
        break;
    case NodeClass::CustomExpression:
    {
        std::string code = is.String();
        int output_type_idx = is.Int32();

        if (m_version > 12001) {
            bool mode = is.Bool();
        }

        int count = is.Int32();
        node.vars.insert({ "input_count", Variant(count) });
        for (int i = 0; i < count; ++i)
        {
            bool foldout_value = is.Bool();
            std::string name = is.String();
            auto type = ENUM_PARSE(is.String(), WirePortDataType);
            std::string internal_data = is.String();
            if (m_version > 12001) {
                auto qualifier = ENUM_PARSE(is.String(), VariableQualifiers);
            }
            if (m_version > 15311) {
                std::string custom_type = is.String();
            }
            if (m_version > 15607) {
                auto precision = ENUM_PARSE(is.String(), PrecisionType);
            }

            node.vars.insert({ "input" + std::to_string(i), Variant(name) });
        }

        if (m_version > 7205) {
            std::string custom_expression_name = is.String();
        }

        if (m_version > 14401) {
            bool generate_unique_name = is.Bool();
        }

        if (m_version > 15102) {
            bool auto_register_mode = is.Bool();
        }

        if (m_version > 15403) {
            std::vector<std::string> dependencies;
            int dependency_count = is.Int32();
            dependencies.reserve(dependency_count);
            for (int i = 0; i < dependency_count; ++i) {
                dependencies.push_back(is.String());
            }
        }
    }
        break;
    case NodeClass::Function:
    {
        std::string filename     = is.String();
        int         order_index  = is.Int32();
        std::string header_title = is.String();

        if (m_version > 7203) {
            int function_graph_id = is.Int32();
        }

        if (m_version > 13704) {
            std::string function_guid = is.String();
        }

        if (m_version > 14203) {
            std::string read_options_helper = is.String();
        }

        node.vars.insert({ "filename", Variant(filename) });
    }
        break;
    case NodeClass::DotProduct:
        LoadDynamicTypeNode(is);
        break;
    case NodeClass::Tex2DAsset:
    {
        PropertyNode prop;
        prop.Load(m_version, is);

        std::string default_tex_guid = is.String();
        if (m_version > 14101) {
            std::string material_tex_guid = is.String();
        }
        bool is_normal_map = is.Bool();
        auto default_tex_value = ENUM_PARSE(is.String(), TexturePropertyValues);
        auto auto_cast_mode = ENUM_PARSE(is.String(), AutoCastType);
        if (m_version > 15306) {
            auto current_type = ENUM_PARSE(is.String(), TextureType);
        } else {
            auto current_type = TextureType::Texture2D;
        }
    }
        break;
    case NodeClass::TexCoords:
    {
        int texcoord_channel = is.Int32();
        if (m_version > 2402) {
            if (m_version > 2404) {
                int ref_node_id = is.Int32();
            } else {
                int ref_array_id = is.Int32();
            }
        }
        if (m_version > 5001) {
            int texcoord_size = is.Int32();
        }

        // for ReadInputDataFromString
        assert(m_version > 7003);
    }
        break;
    case NodeClass::TextureTransform:
    {
        int reference_node_id = is.Int32();
    }
        break;
    case NodeClass::IndirectDiffuseLighting:
        if (m_version > 13002) {
            auto normal_space = ENUM_PARSE(is.String(), ViewSpace);
        }
        break;
    case NodeClass::IndirectSpecularLight:
        if (m_version > 13002) {
            auto normal_space = ENUM_PARSE(is.String(), ViewSpace);
        }
        break;
    case NodeClass::Combine:
    {
        auto selected_output_type = ENUM_PARSE(is.String(), WirePortDataType);
        //for (int i = 0; i < 4; ++i) {
        //    int float_internal_data = is.Int32();
        //}
    }
        break;
    case NodeClass::Switch:
    {
        PropertyNode prop;
        prop.Load(m_version, is);

        int multi_compile = is.Int32();
        if (m_version > 14403) {
            int default_value = is.Int32();
            if (m_version > 14101) {
                int material_value = is.Int32();
            }
        } else {
            int default_value = is.Bool() ? 1 : 0;
            if (m_version > 14101) {
                int material_value = is.Bool();
            }
        }
        if (m_version > 13104)
        {
            bool create_toggle = is.Bool();
            std::string current_keyword = is.String();
        }
        if (m_version > 14001) {
            auto key_word_mode_type = ENUM_PARSE(is.String(), KeywordModeType);
        }
        if (m_version > 14403)
        {
            int key_word_enum_amount = is.Int32();
            std::vector<std::string> default_key_word_names;
            default_key_word_names.reserve(key_word_enum_amount);
            for (int i = 0; i < key_word_enum_amount; ++i) {
                default_key_word_names.push_back(is.String());
            }
        }
    }
        break;
    case NodeClass::StandardSurfaceOutput:
    {
        // OutputNode
        bool is_main_output_node = is.Bool();

        LoadMasterNode(is);

        auto current_light_model = ENUM_PARSE(is.String(), StandardShaderLightModel);
        std::string shader_name = is.String();

        LoadRenderingOptionsOpHelper(is);

        auto cull_mode = ENUM_PARSE(is.String(), CullMode);
        LoadZBufferOpHelper(is);

        auto alpha_mode = ENUM_PARSE(is.String(), AlphaMode);
        float opacity_mask_clip_value = is.Float();
        bool keep_alpha = is.Bool();
        bool cast_shadows = is.Bool();
        int queue_order = is.Int32();
        if (m_version > 11)
        {
            bool custom_blend_mode = is.Bool();
            auto render_type = ENUM_PARSE(is.String(), RenderType);
            if (m_version > 14305) {
                std::string custom_render_type = is.String();
            }
            auto render_queue = ENUM_PARSE(is.String(), RenderQueue);
        }
        if (m_version > 2402) {
            auto render_path = ENUM_PARSE(is.String(), RenderPath);
        }
        if (m_version > 2405) {
            LoadRenderingPlatformOpHelper(is);
        }
        if (m_version > 2500) {
            LoadColorMaskHelper(is);
        }
        if (m_version > 2501) {
            LoadStencilBufferOpHelper(is);
        }
        if (m_version > 2504) {
            LoadTessellationOpHelper(is);
        }
        if (m_version > 2505) {
            bool receive_shadows = is.Bool();
        }
        if (m_version > 3202) {
            LoadBlendOpsHelper(is);
        }
        if (m_version > 3203) {
            int grab_order = is.Int32();
        }
        if (m_version > 5003) {
            LoadOutlineOpHelper(is);
        }
        if (m_version > 5110) {
            LoadBillboardOpHelper(is);
        }
        if (m_version > 6101) {
            auto vertex_mode = ENUM_PARSE(is.String(), VertexMode);
        }
        if (m_version > 6102) {
            int m_shaderLOD = is.Int32();
            LoadFallbackPickerHelper(is);
        }
        if (m_version > 7102) {
            int mask_clip_order_index    = is.Int32();
            int translucency_order_index = is.Int32();
            int refraction_order_index   = is.Int32();
            int tessellation_order_index = is.Int32();
        }
        if (m_version > 10010 && m_version < 15312) {
            LoadAdditionalIncludesHelper(is);
        }
        if (m_version > 11006) {
            LoadCustomTagsHelper(is);
        }
        if (m_version > 13102 && m_version < 15312) {
            LoadAdditionalPragmasHelper(is);
        }
        if (m_version > 13205) {
            bool alpha_to_coverage = is.Bool();
        }
        if (m_version > 13903) {
            LoadDependenciesHelper(is);
        }
        if (m_version > 14005 && m_version < 15312) {
            LoadAdditionalDefinesHelper(is);
        }
        if (m_version > 14501) {
            InlineProperty inline_cull_mode;
            inline_cull_mode.Load(is);
        }
        if (m_version > 14502) {
            int spec_color_order_index = is.Int32();
        }
        if (m_version > 15204) {
            InlineProperty inline_opacity_mask_clip_value;
            inline_opacity_mask_clip_value.Load(is);
        }
        if (m_version > 15311) {
            LoadTemplateAdditionalDirectivesHelper(is);
            LoadAdditionalSurfaceOptionsHelper(is);
        }
        if (m_version > 15402) {
            LoadUsePassHelper(is);
        }

        node.vars.insert({ "light_model", Variant(static_cast<int>(current_light_model)) });
    }
        break;
    }

    node.LoadNodePorts(m_version, is);

    m_nodes.push_back(node);
}

void FileLoader::LoadConn(ImportStream& is)
{
    Connection conn;
    conn.node_to   = is.Int32();
    conn.port_to   = is.Int32();
    conn.node_from = is.Int32();
    conn.port_from = is.Int32();
    m_conns.push_back(conn);
}

void FileLoader::LoadDynamicTypeNode(ImportStream& is)
{
    if (m_version > 10005 /*&& m_extensibleInputPorts*/) {
        int input_count = is.Int32();
    }
}

void FileLoader::LoadMasterNode(ImportStream& is)
{
    if (m_version > 21) {
        int shader_model_idx = is.Int32();
        auto current_precision_type = ENUM_PARSE(is.String(), PrecisionType);
    }
    if (m_version > 2404) {
        std::string custom_inspector_name = is.String();
    }
    if (m_version > 6101) {
        int shader_lod = is.Int32();
    }
    if (m_version > 13001) {
        int master_node_category = is.Int32();
    }
}

void FileLoader::LoadRenderingOptionsOpHelper(ImportStream& is)
{
    //m_codeGenerationDataList.Add(new CodeGenerationData(" Exclude Deferred", "exclude_path:deferred"));
    //m_codeGenerationDataList.Add(new CodeGenerationData(" Exclude Forward", "exclude_path:forward"));
    //m_codeGenerationDataList.Add(new CodeGenerationData(" Exclude Legacy Deferred", "exclude_path:prepass"));
    //m_codeGenerationDataList.Add(new CodeGenerationData(" Shadows", "noshadow"));
    //m_codeGenerationDataList.Add(new CodeGenerationData(" Ambient Light", "noambient"));
    //m_codeGenerationDataList.Add(new CodeGenerationData(" Per Vertex Light", "novertexlights"));
    //m_codeGenerationDataList.Add(new CodeGenerationData(" Lightmaps", "nolightmap "));
    //m_codeGenerationDataList.Add(new CodeGenerationData(" Dynamic Global GI", "nodynlightmap"));
    //m_codeGenerationDataList.Add(new CodeGenerationData(" Directional lightmaps", "nodirlightmap"));
    //m_codeGenerationDataList.Add(new CodeGenerationData(" Built-in Fog", "nofog"));
    //m_codeGenerationDataList.Add(new CodeGenerationData(" Meta Pass", "nometa"));
    //m_codeGenerationDataList.Add(new CodeGenerationData(" Add Pass", "noforwardadd"));
    const int code_generation_data_list_count = 12;
    for (int i = 0; i < code_generation_data_list_count; ++i) {
        bool is_active = is.Bool();
    }
    if (m_version > 10005) {
        bool lod_cross_fade = is.Bool();
    }
    if (m_version > 10007) {
        auto disable_batching = ENUM_PARSE(is.String(), DisableBatchingTagValues);
        bool ignore_projector = is.Bool();
        bool force_no_shadow_casting = is.Bool();
    }
    if (m_version > 11002) {
        bool force_enable_instancing = is.Bool();
    }
    if (m_version > 15205) {
        bool force_disable_instancing = is.Bool();
    }
    if (m_version > 14403) {
        bool specular_highlight_toggle = is.Bool();
        bool reflections_toggle = is.Bool();
    }
}

void FileLoader::LoadZBufferOpHelper(ImportStream& is)
{
    if (m_version < 2502)
    {
        std::string zwrite_mode = is.String();
        std::string ztest_mode = is.String();
    }
    else
    {
        InlineProperty zwrite_mode, ztest_mode;
        if (m_version > 14501) {
            zwrite_mode.Load(is);
            ztest_mode.Load(is);
        } else {
            zwrite_mode.value = static_cast<float>(is.Int32());
            ztest_mode.value  = static_cast<float>(is.Int32());
        }

        bool offset_enabled = is.Bool();

        InlineProperty offset_factor, offset_units;
        if (m_version > 15303) {
            offset_factor.Load(is);
            offset_units.Load(is);
        } else {
            offset_factor.value = is.Float();
            offset_units.value = is.Float();
        }
        if (m_version > 14202) {
            bool extra_depth_pass = is.Bool();
            int extra_ztest_mode = is.Int32();
        }
    }
}

void FileLoader::LoadRenderingPlatformOpHelper(ImportStream& is)
{
		//private readonly string[] RenderingPlatformsLabels =    {   " Direct3D 9",
		//															" Direct3D 11/12",
		//															" OpenGL 3.x/4.x",
		//															" OpenGL ES 2.0",
		//															" OpenGL ES 3.x",
		//															" iOS/Mac Metal",
		//															" Direct3D 11 9.x",
		//															" Xbox 360",
		//															" Xbox One",
		//															" PlayStation 4",
		//															" PlayStation Vita",
		//															" Nintendo 3DS",
		//															" Nintendo Wii U" };
    const int rendering_platform_values_length = 13;
    for (int i = 0; i < rendering_platform_values_length; ++i) {
        bool rendering_platform_value = is.Bool();
    }
}

void FileLoader::LoadColorMaskHelper(ImportStream& is)
{
    const int color_mask_length = 4;
    for (int i = 0; i < color_mask_length; ++i) {
        bool color_mask = is.Bool();
    }
    InlineProperty inline_mask;
    if (m_version > 14501) {
        inline_mask.Load(is);
    }
}

void FileLoader::LoadStencilBufferOpHelper(ImportStream& is)
{
    bool active = is.Bool();

    InlineProperty ref_value;
    InlineProperty read_mask, write_mask;
    InlineProperty comparison_function_idx;
    InlineProperty pass_stencil_op_idx, fail_stencil_op_idx, zfail_stencil_op_idx;
    if (m_version > 14501)
    {
        ref_value.Load(is);
        read_mask.Load(is);
        write_mask.Load(is);
        comparison_function_idx.Load(is);
        pass_stencil_op_idx.Load(is);
        fail_stencil_op_idx.Load(is);
        zfail_stencil_op_idx.Load(is);
    }
    else
    {
        ref_value.value = static_cast<float>(is.Int32());
        read_mask.value = static_cast<float>(is.Int32());
        write_mask.value = static_cast<float>(is.Int32());
        comparison_function_idx.value = static_cast<float>(is.Int32());
        pass_stencil_op_idx.value = static_cast<float>(is.Int32());
        fail_stencil_op_idx.value = static_cast<float>(is.Int32());
        zfail_stencil_op_idx.value = static_cast<float>(is.Int32());
    }
    if (m_version > 13203)
    {
        InlineProperty comparison_function_back_idx;
        InlineProperty pass_stencil_op_back_idx, fail_stencil_op_back_idx, zfail_stencil_op_back_idx;
        if (m_version > 14501)
        {
            comparison_function_back_idx.Load(is);
            pass_stencil_op_back_idx.Load(is);
            fail_stencil_op_back_idx.Load(is);
            zfail_stencil_op_back_idx.Load(is);
        }
        else
        {
            comparison_function_back_idx.value = static_cast<float>(is.Int32());
            pass_stencil_op_back_idx.value = static_cast<float>(is.Int32());
            fail_stencil_op_back_idx.value = static_cast<float>(is.Int32());
            zfail_stencil_op_back_idx.value = static_cast<float>(is.Int32());
        }
    }
}

void FileLoader::LoadTessellationOpHelper(ImportStream& is)
{
    bool enabled = is.Bool();
    int tess_type = is.Int32();
    float tess_factor = is.Float();
    float tess_min_distance = is.Float();
    float tess_max_distance = is.Float();
    if (m_version > 3001)
    {
        bool phong_enabled = is.Bool();
        float phong_strength = is.Float();
    }
}

void FileLoader::LoadBlendOpsHelper(ImportStream& is)
{
    InlineProperty source_factor_rgb, dest_factor_rgb;
    int current_index = is.Int32();
    if (m_version > 15103) {
        source_factor_rgb.Load(is);
        dest_factor_rgb.Load(is);
    } else {
        source_factor_rgb.value = static_cast<float>(ENUM_PARSE(is.String(), AvailableBlendFactor));
        dest_factor_rgb.value = static_cast<float>(ENUM_PARSE(is.String(), AvailableBlendFactor));
    }

    InlineProperty source_factor_alpha, dest_factor_alpha;
    InlineProperty blend_op_rgb, blend_op_alpha;
    int current_alpha_index = is.Int32();
    if (m_version > 15103)
    {
        source_factor_alpha.Load(is);
        dest_factor_alpha.Load(is);

        blend_op_rgb.Load(is);
        blend_op_alpha.Load(is);
        if (m_version < 15404) {
            blend_op_rgb.value += 1;
            blend_op_alpha.value += 1;
        }
    }
    else
    {
        source_factor_alpha.value = static_cast<float>(ENUM_PARSE(is.String(), AvailableBlendFactor));
        dest_factor_alpha.value   = static_cast<float>(ENUM_PARSE(is.String(), AvailableBlendFactor));
        blend_op_rgb.value        = static_cast<float>(ENUM_PARSE(is.String(), AvailableBlendOps));
        blend_op_alpha.value      = static_cast<float>(ENUM_PARSE(is.String(), AvailableBlendOps));
    }
}

void FileLoader::LoadOutlineOpHelper(ImportStream& is)
{
    bool enabled = is.Bool();
    float outline_width = is.Float();
    Color outline_color = StringToColor(is.String());
    if (m_version > 5004) {
        auto mode = ENUM_PARSE(is.String(), OutlineMode);
    }
    if (m_version > 13902) {
        bool m_noFog = is.Bool();
    }
}

void FileLoader::LoadBillboardOpHelper(ImportStream& is)
{
    bool is_billboard = is.Bool();
    auto billboard_type = ENUM_PARSE(is.String(), BillboardType);
    if (m_version > 11007) {
        bool rotation_independent = is.Bool();
    }
}

void FileLoader::LoadFallbackPickerHelper(ImportStream& is)
{
    std::string fallback_shader = is.String();
}

void FileLoader::LoadAdditionalIncludesHelper(ImportStream& is)
{
    int count = is.Int32();
    std::vector<std::string> additional_includes;
    additional_includes.reserve(count);
    for (int i = 0; i < count; ++i) {
        additional_includes.push_back(is.String());
    }
}

void FileLoader::LoadCustomTagsHelper(ImportStream& is)
{
    int count = is.Int32();
    std::vector<std::string> available_tags;
    available_tags.reserve(count);
    for (int i = 0; i < count; ++i) {
        available_tags.push_back(is.String());
    }
}

void FileLoader::LoadAdditionalPragmasHelper(ImportStream& is)
{
    int count = is.Int32();
    std::vector<std::string> additional_pragmas;
    additional_pragmas.reserve(count);
    for (int i = 0; i < count; ++i) {
        additional_pragmas.push_back(is.String());
    }
}

void FileLoader::LoadDependenciesHelper(ImportStream& is)
{
    int count = is.Int32();
    std::vector<std::string> available_dependencies;
    available_dependencies.reserve(count);
    for (int i = 0; i < count; ++i) {
        available_dependencies.push_back(is.String());
    }
}

void FileLoader::LoadAdditionalDefinesHelper(ImportStream& is)
{
    int count = is.Int32();
    std::vector<std::string> additional_defines;
    additional_defines.reserve(count);
    for (int i = 0; i < count; ++i) {
        additional_defines.push_back(is.String());
    }
}

void FileLoader::LoadTemplateAdditionalDirectivesHelper(ImportStream& is)
{
    int count = is.Int32();
    for (int i = 0; i < count; ++i)
    {
        auto line_type = ENUM_PARSE(is.String(), AdditionalLineType);
        std::string line_value = is.String();
        if (m_version > 15607) {
            bool new_item_guid_toggle = is.Bool();
            std::string new_item_guid_value = is.String();
        }
    }
}

void FileLoader::LoadAdditionalSurfaceOptionsHelper(ImportStream& is)
{
    int count = is.Int32();
    std::vector<std::string> available_options;
    available_options.reserve(count);
    for (int i = 0; i < count; ++i) {
        available_options.push_back(is.String());
    }
}

void FileLoader::LoadUsePassHelper(ImportStream& is)
{
    int count = is.Int32();
    for (int i = 0; i < count; ++i)
    {
        std::string location_value = is.String();
        std::string name = is.String();
    }
}

void FileLoader::StringToMultiFloat(const std::string& str, std::vector<float>& multi_flt)
{
    std::vector<std::string> tokens;
    boost::split(tokens, str, boost::is_any_of(","));
    multi_flt.reserve(tokens.size());
    for (auto& t : tokens) {
        multi_flt.push_back(static_cast<float>(std::atof(t.c_str())));
    }
}

FileLoader::Color FileLoader::StringToColor(const std::string& str)
{
    Color col;
    std::vector<std::string> tokens;
    boost::split(tokens, str, boost::is_any_of(","));
    if (tokens.size() >= 4) {
        col.r = static_cast<float>(std::atof(tokens[0].c_str()));
        col.g = static_cast<float>(std::atof(tokens[1].c_str()));
        col.b = static_cast<float>(std::atof(tokens[2].c_str()));
        col.a = static_cast<float>(std::atof(tokens[3].c_str()));
    } else {
        col.r = 1;
        col.g = 1;
        col.b = 1;
        col.a = 1;
    }
    return col;
}

//////////////////////////////////////////////////////////////////////////
// struct FileLoader::Node
//////////////////////////////////////////////////////////////////////////

void FileLoader::Node::LoadNodePorts(int version, ImportStream& is)
{
    // ParentNode::ReadInputDataFromString
    int input_count = 0;
    if (version > 7003) {
        input_count = is.Int32();
    } else {
//        input_count = bp_node->GetAllOutput().size();
    }
    inputs.resize(input_count);
    for (int i = 0; i < input_count; ++i)
    {
        auto& dst = inputs[i];
        if (version < 5003)
        {
            if (version > 23) {
                dst.data_type = ENUM_PARSE(is.String(), WirePortDataType);
            }
            dst.internal_data = is.String();
            if (dst.editable && version >= 3100 && is.IsValid()) {
                dst.name = is.String();
            }
        }
        else
        {
            dst.port_id       = is.Int32();
            dst.data_type     = ENUM_PARSE(is.String(), WirePortDataType);
            dst.internal_data = is.String();
            dst.editable      = is.Bool();
            if (dst.editable && is.IsValid()) {
                dst.name = is.String();
            }
        }
    }

    // ParentNode::ReadOutputDataFromString
    int output_count = 0;
    if (version > 7003) {
        output_count = is.Int32();
    } else {
//        output_count = bp_node->GetAllOutput().size();
    }
    outputs.resize(output_count);
    for (int i = 0; i < output_count; ++i)
    {
        auto& dst = outputs[i];
        dst.data_type = ENUM_PARSE(is.String(), WirePortDataType);
        if (version > 13903) {
            dst.port_id = is.Int32();
        } else {
            dst.port_id = i;
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// struct FileLoader::PropertyNode
//////////////////////////////////////////////////////////////////////////

void FileLoader::PropertyNode::Load(int version, ImportStream& is)
{
    if (version < 2505) {
        std::string property = is.String();
        auto current_parameter_type = property == "Uniform" ?
            PropertyType::Global : ENUM_PARSE(property, PropertyType);
    } else {
        auto current_parameter_type = ENUM_PARSE(is.String(), PropertyType);
    }

    this->name = is.String();
    std::string prop_inspector_name = is.String();
    if (version > 13) {
        int order_index = is.Int32();
    }
    if (version > 4102)
    {
        std::vector<std::string> selected_attr_ibs;
        int attrib_amount = is.Int32();
        selected_attr_ibs.reserve(attrib_amount);
        for (int i = 0; i < attrib_amount; ++i) {
            selected_attr_ibs.push_back(is.String());
        }
    }
    if (version > 14003) {
        auto var_mode = ENUM_PARSE(is.String(), VariableMode);
    }
    if (version > 14201) {
        bool auto_global_name = is.Bool();
    }
    if (version > 14403) {
        int enum_count = is.Int32();
        std::vector<std::string> enum_names;
        std::vector<int>         enum_values;
        enum_names.reserve(enum_count);
        enum_values.reserve(enum_count);
        for (int i = 0; i < enum_count; ++i) {
            enum_names.push_back(is.String());
            enum_values.push_back(is.Int32());
        }
    }
    if (version > 14501) {
        int enum_mode = is.Int32();
        if (enum_mode == 1) {
            std::string enum_class_name = is.String();
        }

        auto auto_register = is.Bool();

        int custom_attr_count = is.Int32();
        std::vector<std::string> custom_attr;
        custom_attr.reserve(custom_attr_count);
        for (int i = 0; i < custom_attr_count; ++i) {
            custom_attr.push_back(is.String());
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// struct FileLoader::InlineProperty
//////////////////////////////////////////////////////////////////////////

void FileLoader::InlineProperty::Load(ImportStream& is)
{
    value   = static_cast<float>(is.Int32());
    active  = is.Bool();
    node_id = is.Int32();
}

}