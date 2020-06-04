#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpath/jsonpath.hpp>

/*
TODO
*/

class Jcat {
public:
    Jcat(jsoncons::json const &notebook, std::ostream &s) : root(notebook), str(s) {}
    int display() {
        if (!is_python(root)) {
            std::cerr << "Support for python only, exit.";
            return -1;
        }

        for (const auto& cell : root.array_range()) {
            display_cell(cell);
        }
    }

private:
    const jsoncons::json &root;
    static const int PAD = 16;
    static const std::string padding;
    std::ostream &str;

    bool is_python(jsoncons::json const &j) {
        auto const & j2 = j.at_or_null(
                "metadata").at_or_null(
                    "kernelspec").at_or_null(
                        "language");
        if (j2.is_null()) return false;
        str << j2.as<std::string>();
        if (j2.as<std::string>() == "python") return true;
        else return false;
    }

    static inline std::string pad_n(int n) { return std::string(n, ' '); }

    void display_cell(jsoncons::json const &cell) {
        bool pad_flag = false;
        show_splitline();

        std::string cell_type = cell["cell_type"].as<std::string>();
        int execution_count = -1;
        if (cell_type == "raw")
            show_header("raw");
        else if (cell_type == "code")
            show_input_count(execution_count = cell["execution_count"].as<int>());
        else if (cell_type == "markdown")
            show_header("markdown");
        else 
            return;

        for (auto const &source_text : cell["source"].array_range()) {
            if (pad_flag)
                str << padding;
            else
                pad_flag = true;
            str << source_text.as<std::string>();
        }
        str << std::endl;

        if  (cell_type == "code" && !cell["outputs"].empty()) {
            if (cell["outputs"][0]["output_type"] == "execute_result") {
                show_output_count(execution_count);
                pad_flag = true;
            }
        }

        for (auto const &output : cell["outputs"].array_range()) {
            std::string output_type = output["output_type"].as<std::string>();
            if (output_type == "stream" && output["name"] == "stderr") {
                show_header("stderr");
                show_textplain(output["text"], false);
            } else if (output_type == "execute_result") {
                show_textplain(output["data"]["text/plain"], true);
            }
            str << std::endl;
        }
    }

    void show_header(std::string hdr) {
        hdr = "`" + hdr + "`";
        int left = (PAD - hdr.size()) / 2;
        str << pad_n(left) << hdr << pad_n(PAD - left - hdr.size());
    }

    void show_splitline() {
        str << padding << 
            "----------------------------------------"
            "---------------------------------\n";
    }

    void show_input_count(int num) {
        std::string num_str = std::to_string(num);
        std::string out = "In [" + num_str + "]: ";
        str << pad_n(PAD - out.size()) << out;
    }

    void show_output_count(int num) {
        std::string num_str = std::to_string(num);
        std::string out = "Out[" + num_str + "]: ";
        str << pad_n(PAD - out.size()) << out;
    }

    void show_textplain(jsoncons::json texts, bool pad_flag) {
        for (auto const &text : texts.array_range()) {
            if (pad_flag) str << padding;
            else pad_flag = true;
            str  << text;
        }
        str << std::endl;
    }
};
const std::string Jcat::padding = std::string(Jcat::PAD, ' ');


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: jcat [file.ipynb]\n";
        return -1;
    }
    std::string fname(argv[1]);

    std::ifstream ifs(fname, std::ios::in);
    std::stringstream buf;
    buf << ifs.rdbuf(); // content available as buf.str()

    const jsoncons::json &nb = jsoncons::json::parse(buf.str());
    Jcat jcat_obj(nb, std::cout);
    int ret = jcat_obj.display();

    ifs.close();
    return ret;
}
