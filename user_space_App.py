driver_handle = open('/proc/pranav_driver')
message_from_kernel_space = driver.handle.readline()
print(message_from_kernel_space)
driver_handle.close()
