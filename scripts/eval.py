import sys
import pandas as pd


def eval(file1, file2):
    code1 = pd.read_csv(file1, delimiter=' ')
    code2 = pd.read_csv(file2, delimiter=' ')

    comp  = pd.DataFrame({'obj1': code1['obj_lnsa'],
                          'obj2': code2['obj_lnsa']})
    best1 = comp[comp.obj1 < comp.obj2]
    best2 = comp[comp.obj1 > comp.obj2]

    print('Analyzing the results:')

    print()

    print('**First implementation**')
    print('Total time   =', code1.time_lnsa.sum())
    print('Best in      =', len(best1))
    print('Relative gap =', sum(best1.obj2 - best1.obj1))

    print()

    print('**Second implementation**')
    print('Total time   =', code2.time_lnsa.sum())
    print('Best in      =', len(best2))
    print('Relative gap =', sum(best2.obj1 - best2.obj2))


if __name__ == "__main__":
    if len(sys.argv) == 3:
        eval(sys.argv[1], sys.argv[2])
    else:
        print('Usage: python3 script.py <file1> <file2>')
        sys.exit(1)
