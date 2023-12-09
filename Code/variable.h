class Variable{
    public:
        Variable(std::string variableName = "unnamed", std::string newType = "uninitialized", std::string newInfo = "uninitialized") : m_variableName(variableName), m_variableType(newType), m_variableInfo(newInfo) {}

        std::string GetName(){ return m_variableName; }
        std::string getType(){ return m_variableType; }
        void setName(std::string newName){ m_variableName = newName; }

    private:
        std::string m_variableName = "unnamed";
        std::string m_variableType = "uninitialized";
        std::string m_variableInfo = "uninitialized";
};