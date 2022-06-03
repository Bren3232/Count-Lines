
// ---- Count Lines of Code in Python, and JavaScript Files ----


use std::fs;

fn main() {

    // Pass path to file in here
    read_file_to_string(String::from(""));
}


fn read_file_to_string(file_path: String) {

    //     Count Lines of Code in Python, and JavaScript Files
    //     ------------------
    //     Pass in path to the target file
    //
    //     Prints
    //     ------
    //     * File Name/Path
    //     * Lines of Code
    //     * Lines that are not code
    //     * Total Lines
    //     * Blank Lines
    //     * Lines that are just comments (counts line as code if comment is after code)
    //
    //     Note: Does not count last line if blank. Counts opening and closing of doc strings,
    //     and single comment symbols as comments.


    println!("---------------- count_lines --------------------------");
    println!("File Name/Path: {}", file_path.as_str());

    let mut lin= vec![];
    let mut f = String::from("");

    let mut code_lines: i64 = 0;
    let mut not_code_lines: i64 = 0;
    let mut only_comments: i64 = 0;
    let mut blank_lines: i64 = 0;
    let mut doc_switch = false;


    if file_path.contains(".js") {
        let comm_symbol = "//";
        f = fs::read_to_string(file_path).expect("Unable to read file");
        let lines = f.lines();
        lin = lines.collect();

        for i in &lin {
            let k = i.trim();
            k.to_string();

            // Handle doc strings as comments
            if k.get(..2) == Some("/*") || doc_switch == true {
                not_code_lines += 1;

                if k != "" {
                    only_comments += 1;
                }
                else {
                    blank_lines += 1;
                }

                doc_switch = true;

                if k.contains("*/") {
                    doc_switch = false;
                }
                continue;
            }

            if k != "" {
                if k.get(..2) != Some(comm_symbol) {
                    code_lines += 1;
                }
                else {
                    not_code_lines += 1;
                    only_comments += 1;
                }
            }
            else {
                not_code_lines += 1;
                blank_lines += 1;
            }
        }
    }

    else {
        let comm_symbol = "#";
        f = fs::read_to_string(file_path).expect("Unable to read file");
        let lines = f.lines();
        lin = lines.collect();

        for i in &lin {
            let k = i.trim();
            k.to_string();

            // Handle doc strings as comments
            if k.contains("'''") && doc_switch == true || k.contains(r#"""#) && doc_switch
                == true {
                doc_switch = false;
                not_code_lines += 1;
                only_comments += 1;
                continue;
            }

            if k.get(..3) == Some("'''") && doc_switch == false || k.get(..3) == Some("\"\"\"") &&
                doc_switch == false {

                if k.get(3..).unwrap().to_string().contains("'''") ||
                    k.get(3..).unwrap().to_string().contains("\"\"\"") {
                    not_code_lines += 1;
                    only_comments += 1;
                    continue;
                }
                else {
                    doc_switch = true;
                }
            }

            if doc_switch == true {
                not_code_lines += 1;
                if k != "" {
                    only_comments += 1;
                }
                else {
                    blank_lines += 1;
                }
            }
            else {
                if k != "" {
                    if k.get(..1) != Some(comm_symbol) {
                        code_lines += 1;
                    }
                    else {
                        not_code_lines += 1;
                        only_comments += 1;
                    }
                }
                else {
                    not_code_lines += 1;
                    blank_lines += 1;
                }
            }
        }
    }

    println!("Lines of Code: {}", code_lines);
    println!("Lines that are not code: {}", not_code_lines);
    println!("Total Lines: {}", lin.len());
    println!("\nBlank Lines: {}", blank_lines);
    println!("Lines that are just comments: {}", only_comments);
    println!("------------------------------------------");

}


