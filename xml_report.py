import xml.etree.ElementTree as ET
import re

tree = ET.parse('report.xml')
root = tree.getroot()

merged_suite = ET.Element('testsuite')
merged_suite.set('name', 'BrasioEngine')

total_tests = 0
total_failures = 0
total_disabled = 0
total_skipped = 0
total_errors = 0
total_time = 0.

for testsuite in root.findall('testsuite'):
    total_tests += int(testsuite.get('tests', 0))
    total_failures += int(testsuite.get('failures', 0))
    total_disabled += int(testsuite.get('disabled', 0))
    total_skipped += int(testsuite.get('skipped', 0))
    total_errors += int(testsuite.get('errors', 0))
    
    time_str = testsuite.get('time', '0')

    if time_str and time_str != '0.':
        try:
            total_time += float(time_str)
        except ValueError:
            pass
    
    for testcase in testsuite.findall('testcase'):
        classname = testcase.get('classname')
        if classname:
            testcase.set('classname', 'BrasioEngine.' + '.'.join(classname.split('_')))

        merged_suite.append(testcase)

merged_suite.set('tests', str(total_tests))
merged_suite.set('failures', str(total_failures))
merged_suite.set('disabled', str(total_disabled))
merged_suite.set('skipped', str(total_skipped))
merged_suite.set('errors', str(total_errors))
merged_suite.set('time', str(total_time) if total_time > 0. else '0.')
merged_suite.set('timestamp', root.get('timestamp', ''))

new_root = ET.Element('testsuites')
for element in ['tests', 'failures', 'disabled', 'skipped', 'errors', 'time', 'timestamp', 'name']:
    new_root.set(element, root.get(element, '0'))

new_root.append(merged_suite)

new_tree = ET.ElementTree(new_root)
ET.indent(new_tree, space = ' ' * 2)
new_tree.write('report.xml', encoding = 'UTF-8', xml_declaration = True)
