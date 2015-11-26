//
//  RSA.h
//  RSA_test2
//
//  Created by Jason on 15/9/8.
//  Copyright (c) 2015年 www.jizhan.com. All rights reserved.
//
/*
 说明：1. iOS客户端加密文件为public_key.der文件 解密文件private_key.p12文件
      2. PHP服务器端加密文件为public_key.pem文件 解密文件为private_key.pem文件
      3. 其中用到的password为创建p12文件时候自己设置的密码
 
 生成私钥公钥的方法
 1. 生成私钥 此文件用于PHP端解密 openssl genrsa -out private_key.pem 1024
 2. openssl req -new -key private_key.pem -out rsaCertReq.csr
 3. openssl x509 -req -days 3650 -in rsaCertReq.csr -signkey private_key.pem -out rsaCert.crt
 4. 生成der文件 此文件用于iOS端加密 openssl x509 -outform der -in rsaCert.crt -out public_key.der
 5. 生成p12文件 此文件用于iOS端解密 openssl pkcs12 -export -out private_key.p12 -inkey private_key.pem -in rsaCert.crt
 6. 根据私钥生成公钥 此文件用于PHP端加密 openssl rsa -in private_key.pem -pubout -out public_key.pem
 */

/*
 PHP服务器端代码
    class RSAEncryptTest {
        //此字段为private_key.pem的字符串
        const PRIVATE_KEY = "-----BEGIN RSA PRIVATE KEY-----
        MIIEpAIBAAKCAQEA0EEC4e0jztQ8Imz+SKhSH1SHap4DimsUsc/GfDY1lULSJ6a0
        k270vqc+w+VzSw8vcrcXKOlvk6UUPxMOk1/EjQt5efqEPaXTumm2xiHHa2DBo+G6
        YvIQmc87zG4gHU+W24v+eCaRl9ioP/2QbKvf6bQQG2I4VCyXF3KhZ8TTP8b24wyW
        JDrvpAipjcJfwHtlYhd7K2kjAmDJ008yumXHz1H5thkppPZj7Azcx2UsY4ERmde5
        t9rOvR5S2QlxQFRkGcjejk7ockcW5OsFmhYIO68YZev6x1fxD9z2TtguE26Acaow
        JHMvf5hHkNve1c8SDy0uXybO8/X9tWIz249tjwIDAQABAoIBAA/t+R94+TU37MWh
        Wq4KGgYFfDo+jfzHhhS31PHpX53kN5kK2mMwqI3w0w8+/Nuv9KwsrxvVB1De3raY
        aZQCTlGPoCIhdH4WsiRfM7jiGpPvGcDEYnJxG634ORXBErnLPbnbcoKUSKy5yNzk
        M2jsmLsSp+zATZi6tG/5t7jtSE9ncFvhcOuewLMU8xxum/9Y1TK1QYgB0yHy+hL+
        wDafAXxLheTEjlgA+/kQGMHUUTkNPYwrSHCLYRcgIOi2CH0PwlI7Onj9KfUggDAv
        W9tPAmVpNZFkSlLviNYDVEP8EOOctCU4UED2ViCYACoUO+TPMxD4Nl9n0iYN6odo
        9s49ASkCgYEA8jzUGp0K9UDyDNZEWSX/q0TfrgoA4laYgo4eCx6zOuUko4SoxCKP
        yWnhQ5SmG8/wMoVQhMTSmrqK04mMzDsdNIvrYABhTltfGbzWbWlnDDVXeHshHLlN
        CXrmsFD38zqM1q2x1S8qoWDDXvKhLEqr5CGaxG7PcpyI2ulTITh1xkMCgYEA3BXq
        NOYjWSAOEvgON7t7PVRL28X6jZb+DQ4ZcunRsi2wAhIPkT7SdW5nWzTWF+lIu9+7
        uVMMNH61m8Ncg1y7bim+0Wzn/LyLfXQXc77CZ7Q/D/qhalMx4W0E3UmxnKhJSnpb
        3HNWmBUFLfabN0PXwmxBZ1qaLe2Cc8Xn15fS9MUCgYEAn8d3sEY94B+CiO0cECF8
        TqATWlzG0ISF/Dd5oaQSXJqgXCs4loaliRkJuOXn2xiBOxGsVqbss5qvz3A/Kscj
        MHHKQ3x8so6aYAOq/Gg1zFuy4ol1AdlH8yTZ3RrLMehA1amkTxXZbLDCrXIk1W47
        izKPP1pIAzU1IBAfAR6YsLkCgYBw7d3LXvtsVAJkwVuqRU0rXwG9t4yk8oFReZad
        XFT5NHBH37SVNsMO9qOaLTZd9poXrOnKYk608P+G+WuTDBYwpMMA+vzetnBs4xDV
        l2Bxjg99x4Dj6eSCY0pHsfStCbzxtm9EYvpf9wk9WHi0lt8zKBE3U0ohnul9NmOM
        QJ9CcQKBgQCL2bd5nmUEjt1LiuAbPlWa+8IZbCGF90inIp0sW41TzL8xpP+vK7nX
        1j07PBcZDCR7ajGQT9FIs+oLERdNQrh7dOKgVXD01QnwHgXk4XE+jrpYhR/LakCK
        icsPRo96FiYNYUGFwYIEV3T4aPvwwXdM67mZmQFS15a3+zDViQhxfw==
        -----END RSA PRIVATE KEY-----";
        //此字段为public_key.pem的字符串
        const PUBLIC_KEY = "-----BEGIN PUBLIC KEY-----
        MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA0EEC4e0jztQ8Imz+SKhS
        H1SHap4DimsUsc/GfDY1lULSJ6a0k270vqc+w+VzSw8vcrcXKOlvk6UUPxMOk1/E
        jQt5efqEPaXTumm2xiHHa2DBo+G6YvIQmc87zG4gHU+W24v+eCaRl9ioP/2QbKvf
        6bQQG2I4VCyXF3KhZ8TTP8b24wyWJDrvpAipjcJfwHtlYhd7K2kjAmDJ008yumXH
        z1H5thkppPZj7Azcx2UsY4ERmde5t9rOvR5S2QlxQFRkGcjejk7ockcW5OsFmhYI
        O68YZev6x1fxD9z2TtguE26AcaowJHMvf5hHkNve1c8SDy0uXybO8/X9tWIz249t
        jwIDAQAB
        -----END PUBLIC KEY-----";
        private static $private_key;
        private static $public_key;
        
        public static function private_encrypt($str){
            self::setup_key();
            if(openssl_private_encrypt($str, $encrypted, self::$private_key))
                return $encrypted;
        }
        public static function private_decrypt($str){
            self::setup_key();
            if(openssl_private_decrypt($str, $decrypted, self::$private_key))
                return $decrypted;
        }
        public static function public_decrypt($str){
            self::setup_key();
            if(openssl_public_decrypt($str, $decrypted, self::$public_key))
                return $decrypted;
        }
        public static function public_encrypt($str){
            self::setup_key();
            if(openssl_public_encrypt($str, $encrypted, self::$public_key))
                return $encrypted;
        }
        private static function setup_key(){
            if (!self::$private_key){
                // 这里的password就是在生成证书的时候设置的私钥密码
                self::$private_key = openssl_pkey_get_private(self::PRIVATE_KEY, "password");
            }
            if (!self::$public_key)
                self::$public_key = openssl_pkey_get_public(self::PUBLIC_KEY);
        }
    }
    //加密
    $a = RSAEncryptTest::public_encrypt('youbing');
    //编码之后打印出来  一定要编码 不然打印不出来
    echo base64_encode($a).'<br>';
    
    //加密之后的字符串
    $ios = "OQzAmrivaHZ8FQsIhP2PHbp11AudZPylbvp22GCZhHhlItzErhH2g3rXdITpAtrRDQQ5ubIfw5I72h9ruTg+uFW0bnHWBQBfvzDmyZfTTmIUD6Cx84w0O3cax1tWoUoQ04mA3yFFughhOf35gQc7mqrO6QqufuNP0A3NVQgnUvmbj9sO7HU1LjDJjGbN7eOGv9MOxBK8JEAJrTE+jaBMduy8+mtfSOZHYiEZ0xu7X1UdDQhYuLPMaLzs5z0w+HesM0WxSKBTmmdue/G4ppD5eYtAx+G0KGmA6QFL+KrIiO9gEORAYjj3BHxiEq1HjLpJsejuQJwXzycyqC5jtM7THw==";
    //需要编码一下才可以解密
    $ios =  base64_decode($ios);
    //解密
    $b = RSAEncryptTest::private_decrypt($a);
    echo $b.'<br>';
 */

#import <Foundation/Foundation.h>

@interface RSA : NSObject

/**
 *  der文件的base64编码值
 */
@property (nonatomic, copy) NSString *public_key;

/**
 *  加载私钥用于解密
 *
 *  @param private_key p12文件的字符串
 *  @param password    生成p12文件时候设置的密码
 */
- (void)loadPrivate_key:(NSString *)private_key password:(NSString *)password;

/**
 *  加密字符串
 *
 *  @param str 需要加密的字符串
 */
- (NSString *)rsaEncryptString:(NSString *)string;

/**
 *  解密字符串
 *
 *  @param string 需要解密的字符串
 */
- (NSString *)rsaDecryptString:(NSString *)string;

@end
