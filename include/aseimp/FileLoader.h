#pragma once

#include "aseimp/typedef.h"
#include "aseimp/Variant.h"

#include <string>
#include <vector>
#include <map>

namespace aseimp
{

class ImportStream;

class FileLoader
{
public:
    struct InputPort
    {
        int              port_id = -1;
        WirePortDataType data_type;
        std::string      internal_data;
        bool             editable = false;
        std::string      name;
    };

    struct OutputPort
    {
        WirePortDataType data_type;
        int              port_id   = -1;
    };

    struct Node
    {
        NodeClass cls;
        int       uid;
        float     x, y;

        std::vector<InputPort>  inputs;
        std::vector<OutputPort> outputs;

        std::map<std::string, Variant> vars;

        void LoadNodePorts(int version, ImportStream& is);
    };

    struct Connection
    {
        int node_to;
        int port_to;
        int node_from;
        int port_from;
    };

public:
    FileLoader() {}

    void LoadAsset(const std::string& filepath);
    void LoadShader(const std::string& filepath);

    auto& GetNodes() const { return m_nodes; }
    auto& GetConns() const { return m_conns; }

private:
    void LoadASE(std::istream& is);

    void LoadNode(ImportStream& is);
    void LoadConn(ImportStream& is);

    void LoadDynamicTypeNode(ImportStream& is);

    void LoadMasterNode(ImportStream& is);

    void LoadRenderingOptionsOpHelper(ImportStream& is);
    void LoadZBufferOpHelper(ImportStream& is);
    void LoadRenderingPlatformOpHelper(ImportStream& is);
    void LoadColorMaskHelper(ImportStream& is);
    void LoadStencilBufferOpHelper(ImportStream& is);
    void LoadTessellationOpHelper(ImportStream& is);
    void LoadBlendOpsHelper(ImportStream& is);
    void LoadOutlineOpHelper(ImportStream& is);
    void LoadBillboardOpHelper(ImportStream& is);
    void LoadFallbackPickerHelper(ImportStream& is);
    void LoadAdditionalIncludesHelper(ImportStream& is);
    void LoadCustomTagsHelper(ImportStream& is);
    void LoadAdditionalPragmasHelper(ImportStream& is);
    void LoadDependenciesHelper(ImportStream& is);
    void LoadAdditionalDefinesHelper(ImportStream& is);
    void LoadTemplateAdditionalDirectivesHelper(ImportStream& is);
    void LoadAdditionalSurfaceOptionsHelper(ImportStream& is);
    void LoadUsePassHelper(ImportStream& is);

    struct PropertyNode
    {
        std::string name;

        void Load(int version, ImportStream& is);
    };

    struct InlineProperty
    {
        float value = 0;
        bool  active = false;
        int   node_id = -1;

        void Load(ImportStream& is);
    };

    struct Color
    {
        float r = 0, g = 0, b = 0, a = 0;
    };

    static void StringToMultiFloat(const std::string& str, std::vector<float>& multi_flt);
    static Color StringToColor(const std::string& str);

private:
    int m_version = 0;

    std::vector<Node> m_nodes;
    std::vector<Connection> m_conns;

}; // FileLoader

}