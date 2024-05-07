#include <Basis/logger.h>

// system
#include <shlobj_core.h>
#include <chrono>
#include <iostream>
#include <fstream>


namespace basis {

    class FileOutput {
    public:
        FileOutput()
            : identitySuffix(generateIdentitySuffix())
            , stream(logFileName(), std::ios_base::out | std::ios_base::app)
            , ready(true)
        {}
        ~FileOutput()
        {
            // this allows other statics to avoid crach when FileOutput is destroyed before em
            ready = false;
        }

        const std::string identitySuffix;
        std::ofstream stream;
        bool ready; // since this object will be static, this is simplest way to prevent other statics from using it

    private:
        std::string logFileName() const
        {
            const std::string result = std::format("{}\\Sandbox.{}.log.txt", getWindowsDocumentsPath(), identitySuffix);
            return result;
        }

        std::string getWindowsDocumentsPath() const {
            TCHAR path[MAX_PATH];
            HRESULT hr = SHGetFolderPath(NULL, CSIDL_COMMON_DOCUMENTS, NULL,
                SHGFP_TYPE_CURRENT, path);

            return std::string(path);
        }
        static std::string generateIdentitySuffix()
        {
            return std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
        }
    };

    FileOutput fileOutput;

    // impl:
    void Logger::printInternal(const std::string& message, const std::string& severity) const
    {
        const std::string fullMessage = std::format("[{}]{} {}", prefix, severity.empty() ? "" : std::format("[{}]", severity), message);
        OutputDebugStringA((fullMessage + "\n").c_str());

        if (true)//targets.contains(Target::console))
        {
            if (severity != "error")
            {
                std::cout << severity << (severity.empty() ? "" : ": ") << message << std::endl;
            }
            else
            {
                std::cout << "error:" << message << std::endl;
                std::cerr << message << std::endl;
            }
        }

        if (true)//targets.contains(Target::file))
        {
            if (fileOutput.ready)
                fileOutput.stream << fullMessage << std::endl; // flushes every string
            else
            {
                //gocha!
                std::cout << "log file is closed and can not be used" << std::endl;
            }
        }

    }

    void Logger::print(const std::string& message) const
    {
        printInternal(message, "");
    }

    void Logger::error(const std::string& message) const
    {
        printInternal(message, "error");
    }

    void Logger::critical(const std::string& message) const
    {
        printInternal(message, "critical");
        throw std::logic_error(std::format("critical: {}", message));
    }



}