package leetcode

// 415 https://leetcode-cn.com/problems/add-strings/

func sumByte(a, b byte, shift int) (byte, int) {
	v := int(a-'0') + int(b-'0') + shift
	shift = v / 10
	return byte(v%10) + '0', shift
}

func addStrings(num1 string, num2 string) string {
	sum := make([]byte, 0)
	num1Bytes := []byte(num1)
	num2Bytes := []byte(num2)
	i := len(num1Bytes) - 1
	j := len(num2Bytes) - 1
	shift := 0
	var b byte

	for i >= 0 && j >= 0 {
		b, shift = sumByte(num1Bytes[i], num2Bytes[j], shift)
		sum = append(sum, b)
		i--
		j--
	}
	for i >= 0 {
		b, shift = sumByte(num1Bytes[i], '0', shift)
		sum = append(sum, b)
		i--
	}
	for j >= 0 {
		b, shift = sumByte('0', num2Bytes[j], shift)
		sum = append(sum, b)
		j--
	}
	if shift >0 {
		sum = append(sum, '1')
	}

	ret := make([]byte, 0)
	for i := len(sum) - 1; i >= 0; i-- {
		ret = append(ret, sum[i])
	}
	return string(ret)
}
