from setuptools import setup

package_name = 'py_pubsub'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='automaticaddison',
    maintainer_email='automaticaddison@todo.todo',
    description='A minimal publisher/subscriber that uses the ROS Python Client Library',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
                'my_publisher = py_pubsub.my_publisher_node:main',
        ],
},
)
