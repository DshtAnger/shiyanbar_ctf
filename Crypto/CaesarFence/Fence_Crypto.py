#coding:utf-8
def fence_Crypto(msg,priority="row"):
    '''
    usage:
        fence_Crypto(msg[, priority]) ---> to encrypt or decrypt the msg with fence crypto
    args:
        msg:
            a plaintext which will be crypted or a ciphertext which will be decrypted
        priority:
            row priority or column priority,default is the former
    return:
        result:
            if msg is plaintext,it contains all of possible ciphertext.
            if msg is ciphertext,it contains all of possible plaintext
    '''
    msg_len = len(msg)
    row_num = 1
    result = []
    if priority == "row":        
        while row_num<=msg_len:    
            temp = [msg[block_num::row_num] for block_num in xrange(row_num)]
            result.append("".join(temp))
            row_num += 1
        return result
    elif priority == "columns":
        pass
    else:
        print "parameter error!please help(fence_Crypto)"