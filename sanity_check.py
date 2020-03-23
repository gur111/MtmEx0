import string
import unittest
import random
import psutil
import subprocess as sp

TOT_PATH = './cmake-build-debug/mtm_tot'
SOL_PATH = './part1/mtm_sol'

REPEAT_COUNT = 50000


def generate_invalid():
    """
    This is likely an invalid number
    :return:
    """
    return ''.join(random.choices('+-' + string.ascii_lowercase + string.digits, k=random.randint(1, 10))).encode()


def generate_valid(length=10):
    return (random.choice(['', '-', '+']) + ''.join(random.choices(string.digits, k=random.randint(1, length)))).encode()


def is_int(s):
    try:
        return int(s, base=10)
    except ValueError:
        return False


class MyTestCase(unittest.TestCase):
    def test_invalids(self):

        for _ in range(REPEAT_COUNT):
            count = random.choice([generate_invalid(), generate_valid(length=6), generate_valid(length=6),
                                   generate_valid(length=6), generate_valid(length=6)])
            num_as_int = is_int(count)

            tot = sp.Popen([TOT_PATH], stdin=sp.PIPE, stdout=sp.PIPE, stderr=sp.PIPE)
            sol = sp.Popen([SOL_PATH], stdin=sp.PIPE, stdout=sp.PIPE, stderr=sp.PIPE)

            # print(f'Checking num: {num.decode()}')
            tot.stdin.write(count)
            sol.stdin.write(count)

            tot_out = tot.communicate()
            sol_out = sol.communicate()
            self.assertEqual(sol_out, tot_out, f"Output incompatible. Count: {count}\n"
                                               f"Free memory: {psutil.virtual_memory().available / (1024 ** 2)}MB")
            # print(f'Output was: {tot_out}')

            if num_as_int:
                for _ in range(num_as_int + random.randint(-2, 3)):
                    sol_out = sol.poll()
                    tot_out = tot.poll()
                    self.assertEqual(sol_out, tot_out, f"Poll incompatible")
                    if not tot.poll():
                        break

                    num = random.choice([generate_invalid(), generate_valid(),
                                         generate_valid(), generate_valid(), generate_valid()])
                    tot.stdin.write(num)
                    sol.stdin.write(num)
                    sol_out = sol.communicate()
                    tot_out = tot.communicate()
                    self.assertEqual(sol_out, tot_out, f"Output incompatible. Num: {num}. Count: {count}")

    def test_valids(self):

        for _ in range(REPEAT_COUNT):
            count = generate_valid(length=6)

            tot = sp.Popen([TOT_PATH], stdin=sp.PIPE, stdout=sp.PIPE, stderr=sp.PIPE)
            sol = sp.Popen([SOL_PATH], stdin=sp.PIPE, stdout=sp.PIPE, stderr=sp.PIPE)

            # print(f'Checking num: {num.decode()}')
            tot.stdin.write(count)
            sol.stdin.write(count)

            tot_out = tot.communicate()
            sol_out = sol.communicate()
            self.assertEqual(sol_out, tot_out, f"Output incompatible. Count: {count}\n"
                                               f"Free memory: {psutil.virtual_memory().available / (1024 ** 2)}MB")
            # print(f'Output was: {tot_out}')

            for _ in range(int(count) + random.randint(-2, 3)):
                sol_out = sol.poll()
                tot_out = tot.poll()
                self.assertEqual(sol_out, tot_out, f"Poll incompatible")
                if not tot.poll():
                    break

                num = generate_valid()

                tot.stdin.write(num)
                sol.stdin.write(num)
                sol_out = sol.communicate()
                tot_out = tot.communicate()
                self.assertEqual(sol_out, tot_out, f"Output incompatible. Num: {num}, Count: {count}")


if __name__ == '__main__':
    unittest.main()
