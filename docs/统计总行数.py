import os

def get_all_files(directory):
    file_list = []
    
    # 遍历目录下的所有文件和子目录
    for root, directories, filenames in os.walk(directory):
        # 遍历当前目录下的文件
        for filename in filenames:
            # 构建文件的完整路径
            file_path = os.path.join(root, filename)
            file_list.append(file_path)
    
    return file_list

def count_lines_in_files(file_list):
    total_lines = 0
    
    # 遍历文件列表
    for file_path in file_list:
        # 打开文件进行逐行读取
        with open(file_path, 'r', encoding='utf-8') as file:
            # 逐行计数
            lines = file.readlines()
            total_lines += len(lines)
    
    return total_lines


def statistics(directory):
    # 获取目录下的全部文件
    files = get_all_files(directory)
    # 统计文件总行数
    total_lines = count_lines_in_files(files)

    print(f"{directory}\n\tTotal lines:", total_lines)
    return total_lines

file1 = statistics('D:\HaaaaaalloMg\Workplace\Hydrogen\hdg\include')
file2 = statistics('D:\HaaaaaalloMg\Workplace\Hydrogen\hdg\src')
print(f'总行数为：{file1+file2}')

    
