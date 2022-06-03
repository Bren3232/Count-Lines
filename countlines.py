
# ---- Count Lines of Code in Python, and JavaScript Files ----


def count_lines(file_path):
    '''
    Count Lines of Code in Python, and JavaScript Files
    ------------------
    Pass in __file__ if running from a Python target file,
    otherwise pass in path

    Prints
    ------
    * File Name/Path
    * Lines of Code
    * Lines that are not code
    * Total Lines
    * Blank Lines
    * Lines that are just comments (counts line as code if comment is after code)

    Note: Does not count last line if blank. Counts opening and closing of doc strings,
    and single comment symbols as comments.
    '''

    print('---------------- count_lines --------------------------')
    print('File Name/Path: ', file_path)

    code_lines = 0
    not_code_lines = 0
    only_comments = 0
    blank_lines = 0
    doc_switch = False


    if file_path[-3:] == '.js':
        comm_symbol = '//'
        f = open(file_path, "r")
        lines = f.read().splitlines()

        for i in lines:
            k = i.strip()

            # Handle doc strings as comments
            if k[:2] == '/*' or doc_switch == True:
                not_code_lines += 1
                if k != '':
                    only_comments += 1
                else:
                    blank_lines += 1
                doc_switch = True
                if '*/' in k:
                    doc_switch = False
                continue

            if k != '':
                if k[:2] != comm_symbol:
                    code_lines += 1
                else:
                    not_code_lines += 1
                    only_comments += 1
            else:
                not_code_lines += 1
                blank_lines += 1

        f.close()

    else:
        comm_symbol = '#'
        f = open(file_path, "r")
        lines = f.read().splitlines()

        for i in lines:
            k = i.strip()

            # Handle doc strings as comments
            # Turn off
            if "'''" in k and doc_switch == True or '"""' in k and doc_switch == True:
                doc_switch = False
                not_code_lines += 1
                only_comments += 1
                continue

            # Turn on
            if k[:3] == "'''" and doc_switch == False or k[:3] == '"""' and doc_switch == False:
                if "'''" in k[3:] or '"""' in k[3:]:
                    not_code_lines += 1
                    only_comments += 1
                    continue
                else:
                    doc_switch = True

            if doc_switch == True:
                not_code_lines += 1
                if k != '':
                    only_comments += 1
                else:

                    blank_lines += 1
            else:
                if k != '':
                    if k[0] != comm_symbol:
                        code_lines += 1
                    else:
                        not_code_lines += 1
                        only_comments += 1
                else:
                    not_code_lines += 1
                    blank_lines += 1

        f.close()


    print('Lines of Code: ', code_lines)
    print('Lines that are not code: ', not_code_lines)
    print('Total Lines: ', len(lines))
    print('\nBlank Lines: ', blank_lines)
    print('Lines that are just comments: ', only_comments)
    print('------------------------------------------')

    # print(lines)

if __name__ == "__main__":
    # When using here run this, with path inside
    count_lines('')

