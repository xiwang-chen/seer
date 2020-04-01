while True:
    user_input = list( input( '请输入电池报文：' ).split( ' ' ) )
    if user_input[0].lower() == '7e' and user_input[-1].lower() == '0d':
        # 计算电池的温度：
        temperature_one = [chr(int(b,16)) for b in user_input[-39:-35]]
        temperature_one_sum = ''.join(temperature_one)
        temperature_one_true = int(temperature_one_sum,16)-40

        temperature_two = [chr(int(b,16)) for b in user_input[-35:-31]]
        temperature_two_sum = ''.join(temperature_two)
        temperature_two_true = int(temperature_two_sum,16) - 40

        temperature_three = [chr(int(b,16)) for b in user_input[-31:-27]]
        temperature_three_sum = ''.join(temperature_three)
        temperature_three_true = int(temperature_three_sum,16) - 40

        b = max(temperature_one_true,temperature_two_true,temperature_three_true)
        print('报文信息:')
        print('当前温度值：{}℃'.format(b))

        # 下面是计算一合电池的电流值：
        electric_current = [chr(int(b,16)) for b in user_input[-27:-23]]
        str_sum = ''.join(electric_current)
        value = int(str_sum,16)
        if value >= 32767:
            pack = (value - 65536) / 100
            print('放电电流值:{}A'.format(pack))
        else:
            pack = value / 100
            print('充电电流值:{}A'.format(pack))

        # 计算电池的电压：
        voltage_range = [chr( int( b, 16 ) ) for b in user_input[-23:-19]]
        voltage_sum = ''.join(voltage_range)
        voltage_true = int(voltage_sum,16)/1000
        print('当前电压值:{:.2f}V'.format(voltage_true))

        # 计算电池剩余电量的百分比：
        remaining_vol = [chr( int( b, 16 ) ) for b in user_input[-19:-15]]
        remaining_vol_sum = ''.join(remaining_vol)

        remaining_all = [chr( int( b, 16 ) ) for b in user_input[-13:-9]]
        remaining_all_sum = ''.join(remaining_all)
        vol_true = int(remaining_vol_sum,16)/int(remaining_all_sum,16)
        print( '剩余电量值:{:.2f}%'.format(vol_true*100 ) )



        # 计算电池的充电次数
        recharge_dicharge_time = [chr( int( b, 16 ) ) for b in user_input[-9:-5]]
        recharge_dicharge_time_sum = ''.join( recharge_dicharge_time )
        recharge_dicharge_time_sum_true = int(recharge_dicharge_time_sum,16)
        print('充放电次数:{}次'.format( recharge_dicharge_time_sum_true ) )

        affirm_again = input('是否检测下一次电池报文信息(y/n):')
        if affirm_again == 'y':
            continue
        else:
            break
    else:
        print('您输入的报文有错，请重新输入，谢谢!')
        continue