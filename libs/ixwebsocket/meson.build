project('ixwebsocket', 'cpp')

cxx = meson.get_compiler('cpp')

deps = [
    dependency('threads'),
    cxx.find_library('curl')
]

srcs = [
    'IXBench.cpp',
    'IXCancellationRequest.cpp',
    'IXConnectionState.cpp',
    'IXDNSLookup.cpp',
    'IXExponentialBackoff.cpp',
    'IXGetFreePort.cpp',
    'IXGzipCodec.cpp',
    'IXHttp.cpp',
    'IXHttpClient.cpp',
    'IXHttpServer.cpp',
    'IXNetSystem.cpp',
    'IXSelectInterrupt.cpp',
    'IXSelectInterruptEvent.cpp',
    'IXSelectInterruptFactory.cpp',
    'IXSelectInterruptPipe.cpp',
    'IXSetThreadName.cpp',
    'IXSocket.cpp',
    'IXSocketAppleSSL.cpp',
    'IXSocketConnect.cpp',
    'IXSocketFactory.cpp',
    'IXSocketMbedTLS.cpp',
    'IXSocketOpenSSL.cpp',
    'IXSocketServer.cpp',
    'IXSocketTLSOptions.cpp',
    'IXStrCaseCompare.cpp',
    'IXUdpSocket.cpp',
    'IXUrlParser.cpp',
    'IXUserAgent.cpp',
    'IXUuid.cpp',
    'IXWebSocket.cpp',
    'IXWebSocketCloseConstants.cpp',
    'IXWebSocketHandshake.cpp',
    'IXWebSocketHttpHeaders.cpp',
    'IXWebSocketPerMessageDeflate.cpp',
    'IXWebSocketPerMessageDeflateCodec.cpp',
    'IXWebSocketPerMessageDeflateOptions.cpp',
    'IXWebSocketProxyServer.cpp',
    'IXWebSocketServer.cpp',
    'IXWebSocketTransport.cpp'
]

ixwebsocket_lib =  static_library(
    'ixwebsocket', srcs, dependencies: deps,
    include_directories: ['.', '..'],
    override_options: ['cpp_std=c++20', 'buildtype=release']
)

ixwebsocket_dep = declare_dependency(
    include_directories: ['.', '..'],
    link_with: ixwebsocket_lib
)
