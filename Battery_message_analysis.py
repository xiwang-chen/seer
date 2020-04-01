print('----------seer----------\n\n请注意：此报文解析只适用于标准的1363协议!'
      '\n用户自定义部分，请通知我司进行适配！\n\n----------seer----------\n')
while True:
    user_input = list( input( '请输入电池报文：' ).split( ' ' ) )
    if user_input[0].lower() == '7e' and user_input[-1].lower() == '0d':

        print('报文信息:\n')

        # Pack的数量
        pack_num = [chr(int(b, 16)) for b in user_input[15:17]]
        pack_num_sum = ''.join(pack_num)
        pack_num_true = int(pack_num_sum, 16)
        print('pack的数量：{}\n'.format(pack_num_true))

        # 自动识别串联电池包数：m
        batteries_connect_num = [chr(int(b, 16)) for b in user_input[17:19]]
        batteries_connect_num_sum = ''.join(batteries_connect_num)
        batteries_connect_num_true = int(batteries_connect_num_sum, 16)
        print('当前的m值：{}\n'.format(batteries_connect_num_true))

        #自动识别温度传感器数量：n
        n_front = batteries_connect_num_true * 4 + 19
        n_behind = batteries_connect_num_true * 4 + 21
        temperatures_num = [chr(int(b, 16)) for b in user_input[n_front:n_behind]]
        temperatures_num_sum = ''.join(temperatures_num)
        temperatures_num_true = int(temperatures_num_sum, 16)
        print('温度传感器数：{}\n'.format(temperatures_num_true))

        # 计算电池的温度：
        num = 1
        tem = []
        while num <= temperatures_num_true:

            tempe_n_front = (n_behind) + (num - 1) * 4
            tempe_n_behind = tempe_n_front + 4
            temperature_one = [chr(int(b, 16)) for b in user_input[tempe_n_front:tempe_n_behind]]
            temperature_one_sum = ''.join(temperature_one)
            temperature_one_true = [int(temperature_one_sum, 16) - 40]
            tem.append(temperature_one_true)
            num += 1
        print('当前温度值：{}℃\n'.format(int(max(tem).pop())))

        # 下面是计算一合电池的电流值：
        electric_current = [chr(int(b,16)) for b in user_input[tempe_n_behind:tempe_n_behind + 4]]
        str_sum = ''.join(electric_current)
        value = int(str_sum,16)
        if value >= 32767:
            pack = (value - 65536) / 100
            print('放电电流值:{}A\n'.format(pack))
        else:
            pack = value / 100
            print('充电电流值:{}A\n'.format(pack))

        # 计算电池的电压：
        voltage_range = [chr( int( b, 16 ) ) for b in user_input[tempe_n_behind + 4 :tempe_n_behind + 8]]
        voltage_sum = ''.join(voltage_range)
        voltage_true = int(voltage_sum,16)/1000
        print('当前电压值:{:.2f}V\n'.format(voltage_true))

        # 计算电池剩余电量的百分比：
        remaining_vol = [chr( int( b, 16 ) ) for b in user_input[tempe_n_behind + 8:tempe_n_behind + 12]]
        remaining_vol_sum = ''.join(remaining_vol)

        remaining_all = [chr( int( b, 16 ) ) for b in user_input[-13:-9]]
        remaining_all_sum = ''.join(remaining_all)
        vol_true = int(remaining_vol_sum,16)/int(remaining_all_sum,16)
        print( '剩余电量值:{:.2f}%\n'.format(vol_true*100 ) )



        # 计算电池的充电次数
        recharge_dicharge_time = [chr( int( b, 16 ) ) for b in user_input[-9:-5]]
        recharge_dicharge_time_sum = ''.join( recharge_dicharge_time )
        recharge_dicharge_time_sum_true = int(recharge_dicharge_time_sum,16)
        print('充放电次数:{}次\n'.format( recharge_dicharge_time_sum_true ) )

        affirm_again = input('是否检测下一次电池报文信息(y/n):')
        if affirm_again == 'y':
            continue
        else:
            break
    else:
        print('您输入的报文有错，请重新输入，谢谢!')
        continue