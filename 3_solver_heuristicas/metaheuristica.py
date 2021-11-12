
def Read_data(path):
    
    import copy
    
    coords_x = []
    coords_y = []
    bacias = []
    nomes = []
    maturidades = []
    qualidades = []
    plays = []
    soterramentos = []
    pcgnas = []
    geracao = []
    migracao = []
    reservatorio = []
    geometria = []
    retencao = []
    pshc = []
    mc_vol = []
    mi_vol = []
    mc_vpl = []
    mi_vpl = []
    custos = []
    tempos_exec = []
    inicio_janela = []
    final_janela = []
    sondas_x = []
    sondas_y = []
    
    data = {
        1: coords_x,
        2: coords_y,
        3: bacias,
        4: nomes,
        5: maturidades,
        6: qualidades,
        7: plays,
        8: soterramentos,
        9: pcgnas,
        10: geracao,
        11: migracao,
        12: reservatorio,
        13: geometria,
        14: retencao,
        15: pshc,
        16: mc_vol,
        17: mi_vol,
        18: mc_vpl,
        19: mi_vpl,
        20: custos,
        21: tempos_exec,
        22: inicio_janela,
        23: final_janela,
        25: sondas_x,
        26: sondas_y
    }
    
    setup = []
    
    with open(path, 'r') as f:
        for i, line in enumerate(f):
            if i == 0:
                n_projetos = int(line.split()[0])
                custo_total = float(line.split()[1])
                t_init = int(line.split()[2])
                t_final = int(line.split()[3])
                delta_t = int(line.split()[4])
                n_periodos = int(line.split()[5])
            elif i == 24:
                n_sondas = int(line.split()[0])
            elif i <= 26:
                for elem in line.split():
                    try:
                        data[i].append(float(elem))
                    except:
                        data[i].append(elem)
            elif i > 26:
                setup.append([])
                for elem in line.split():
                    setup[i - 27].append(float(elem))
    
    return n_projetos, n_sondas, n_periodos, t_init, t_final, delta_t, custo_total, data, setup

class Node:
    
    """
    Documentação:
    """
    
    def __init__(self, data=None):
        self.data = data
        self.next = None
        self.prev = None
    

class DoublyLinkedList:
    
    """
    Documentação:
    """
    
    def __init__(self, nodes=None):
        self.head = None
        if nodes is not None:
            node = Node(data=nodes.pop(0))
            self.head = node
            for elem in nodes:
                new_node = Node(data=elem)
                node.next = new_node
                new_node.prev = node
                node = node.next
    
    def __iter__(self):
        node = self.head
        while node is not None:
            yield node
            node = node.next
    
    def add_node_begining(self, value_to_add):
        new_node = Node(data=value_to_add)
        
        if not self.head:
            self.head = new_node
            return
        
        new_node.next = self.head
        self.head.prev = new_node
        self.head = new_node
    
    def add_node_end(self, value_to_add):
        
        new_node = Node(data=value_to_add)
        
        if not self.head:
            self.head = new_node
            return
        
        for curr in self:
            pass
        curr.next = new_node
        new_node.prev = curr
    
    def add_node_after_node(self, value_to_add, node_ref):
        new_node = Node(data=value_to_add)
        new_node.next = node_ref.next
        new_node.prev = node_ref
        if (node_ref.next != None):
            node_ref.next.prev = new_node
        node_ref.next = new_node
    
    def add_node_before_node(self, value_to_add, node_ref):
        new_node = Node(data=value_to_add)
        if node_ref == self.head:
            self.head.prev = new_node
            new_node.next = self.head
            self.head = new_node
        else:
            node_ref.prev.next = new_node
            new_node.prev = node_ref.prev
            new_node.next = node_ref
            node_ref.prev = new_node
    
    def remove_node_by_ref(self, node):
        if node == self.head:
            if (node.next != None):
                node.next.prev = None
                self.head = node.next
            del node
        else:
            if (node.next != None):
                node.next.prev = node.prev
                node.prev.next = node.next
            else:
                node.prev.next = node.next
            del node
    
    def find_value(self, value):
        for node in self:
            if node.data == value: break
        return node

def VerificarSondas(s, sondas, debug=False):
    
    """
    Documentação:
    
    Verfica tempo livre de cada sonda
    
    """
    
    result = True
    
    if (sondas == []):
        
        if (debug):
            print ("Lista de sondas errada: sondas = ", sondas)
        
        return False
    
    for sonda in s.keys():
        val = 0
        for node in s[sonda]:
            if (node.data[0] == -1):
                val += node.data[2] - node.data[1] + 1
        flag_found = False
        for (key, value) in sondas:
            if (value == sonda):
                flag_found = True
                if (key != - val):
                    if (debug):
                        print ("Lista de sondas errada: sonda ", sonda, " tem ", -val, " livre, mas ", key, " indicado")
                    return False
        
        if (not flag_found):
            if (debug):
                print ("Lista de sondas errada: sonda ", sonda, " não encontrada na lista de sondas=", sondas)
            return False
    
    if (debug):
        print ("Lista de sondas correta")
    
    return result

def VerificaMaxFree(s, max_free, debug=False):
    
    """
    Documentação:
    
    Verifica tamanho da janela de tempo da sonda com mais tempo disponível
    
    """
    
    val = 0
    for sonda in s.keys():
        val_temp = 0
        for node in s[sonda]:
            if (node.data[0] == -1):
                val_temp += node.data[2] - node.data[1] + 1
        if (val_temp > val):
            val = val_temp
    
    if (debug):
        if round(val, 5) == round(-max_free, 5):
            print ('max free correto: ', - max_free)
        else:
            print ('max free incorreto: ', -max_free, ' reportado, e ', val, ' apurado')
    
    return round(val, 5) == round(-max_free, 5)

def VerificaTotalFree(s, total_free, debug=False):
    
    """
    Documentação:
    
    Verifica tempo total diponível na solução
    
    """
    
    val = 0
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] == -1):
                val += node.data[2] - node.data[1] + 1
    
    if (debug):
        if round(val, 5) == round(total_free, 5):
            print ('total free correto: ', total_free)
        else:
            print ('total free incorreto: ', total_free, ' reportado, e ', val, ' apurado')
    
    return round(val, 5) == round(total_free, 5)

def VerificaTotalSetup(s, total_setup, desloc, debug=False):
    
    """
    Documentação:
    
    Verifica tempo total de deslocamento entre projetos da solução
    
    """
    
    lag = len(s.keys())
    
    val = 0
    for sonda in s.keys():
        prev = None
        for node in s[sonda]:
            if (node.data[0] != -1):
                if (prev == None):
                    val += desloc[sonda][node.data[0] + lag]
                else:
                    val += desloc[prev + lag][node.data[0] + lag]
                prev = node.data[0]
    
    if (debug):
        if round(val, 5) == round(total_setup, 5):
            print ('total setup correto: ', total_setup)
        else:
            print ('total setup incorreto: ', total_setup, ' reportado, e ', val, ' apurado')
    
    return round(val, 5) == round(total_setup, 5)

def VerificaFuncaoObjetivo(s, valor, dados, debug=False):
    
    """
    Documentação:
    """
    
    fitness = 0
    for sonda in s.keys():
        for node in s[sonda]:
            
            if node.data[0] != -1:
                fitness += dados[19][node.data[0]]
    
    if (debug):
        if round(fitness, 5) == round(valor, 5):
            print ('função objetivo correta: ', fitness)
        else:
            print ('função objetivo incorreta: ', valor, ' reportado, e ', fitness, ' apurado')
    
    return round(fitness, 5) == round(valor, 5)

def VerificaRestricaoOrcamento(s, valor, dados, debug=False):
    
    """
    Documentação:
    """
    
    custo = 0
    for sonda in s.keys():
        for node in s[sonda]:
            
            if node.data[0] != -1:
                custo += dados[20][node.data[0]]
    
    if (debug):
        if round(custo, 5) == round(valor, 5):
            print ('orçamento correto: ', custo)
        else:
            print ('orçamento incorreto: ', valor, ' reportado, e ', custo, ' apurado')
    
    return round(custo, 5) == round(valor, 5)

def VerificaRestricaoUnicidadeProjetos(s, dados, debug=False):
    
    """
    Documentação:
    """
    
    result = True
    projetos = set()
    for sonda in s.keys():
        for node in s[sonda]:
            
            if node.data[0] != -1:
                if node.data[0] in projetos:
                    result = False
                    if (debug):
                        print ('unicidade incorreta: projeto ', node.data[0], ' duplicado')
                    return result
                else:
                    projetos.add(node.data[0])
    
    if (debug):
        print ('unicidade correta')
    
    return result

def VerificaRestricaoTimeWindows(s, dados, debug=False):
    
    """
    Documentação:
    """
    
    result = True
    for sonda in s.keys():
        for node in s[sonda]:
            
            if node.data[0] != -1:
                if not ((node.data[1] >= dados[22][node.data[0]])  and (node.data[1] <= dados[23][node.data[0]])):
                    result = False
                    if (debug):
                        print ('janelas de tempo incorretas: projeto ', node.data[0], ' tem contrato de ', 
                              dados[22][node.data[0]], ' a ', dados[23][node.data[0]], ' e está alocado de ', 
                              node.data[1], ' a ', node.data[2])
                    return result
    
    if (debug):
        print ('janelas de tempo corretas')
    
    return result

def VerificaRestricaoScheduling(s, dados, desloc, debug=False):
    
    """
    Documentação:
    """
    
    lag = len(s.keys())
    
    result = True
    for sonda in s.keys():
        for node in s[sonda]:
            
            if node.data[0] != -1:
                
                # se projeto vem após origem da sonda
                if (node.prev == None):
                    setup = desloc[sonda][node.data[0]+lag]
                elif ( (node.prev.data[0] == -1) and (node.prev.prev == None) ):
                    setup = desloc[sonda][node.data[0]+lag]
                # senão, projeto vem após algum outro projeto
                else:
                    # se existe janela de sonda antes do projeto
                    if node.prev.data[0] == -1:
                        setup = desloc[node.prev.prev.data[0]+lag][node.data[0]+lag]
                    # senão, ele vem imediatamente após o outro projeto
                    else:
                        setup = desloc[node.prev.data[0]+lag][node.data[0]+lag]
                
                if (node.data[2]-node.data[1] + 1 != setup + dados[21][node.data[0]]):
                    result = False
                    if (debug):
                        print ('setup incorreto: projeto ', node.data[0], ' alocado de ', 
                               node.data[1], ' a ', node.data[2], ', sendo setup=', setup, ' e proc. time=', 
                              dados[21][node.data[0]], ' logo, ', node.data[2]-node.data[1]+1, ' != ', 
                              setup + dados[21][node.data[0]])
                    return result
    
    if (debug):
        print ('setup correto')
    
    return result

def VerificaRestricaoContinuidade(s, debug=False):
    
    """
    Documentação:
    """
    
    result = True
    for sonda in s.keys():
        for node in s[sonda]:
            
            if (node.data[2] < node.data[1]):
                result = False
                if (debug):
                    print ("Continuidade incorreta: tempo de início maior que tempo final")
                return result
            
            if (node.next != None):
                if (node.next.data[1] != node.data[2] + 1):
                    result = False
                    if (debug):
                        print ("Continuidade incorreta: sequência não está na ordem de tempo")
                    return result
    
    if (debug):
        print ("Continuidade correta")
    
    return result

def VerificaRestricoes(s, dados, valor_fit, valor_custos, desloc, sondas, max_free, total_free, total_setup,
                      debug=False):
    
    """
    Documentação:
    """
    
    import CPUtimer
    
    if debug:
        timer = CPUtimer.CPUTimer()
        timer.reset()
        timer.start()
    
    fo = VerificaFuncaoObjetivo(s, valor_fit, dados, debug)
    
    orc = VerificaRestricaoOrcamento(s, valor_custos, dados, debug)
    
    unic = VerificaRestricaoUnicidadeProjetos(s, dados, debug)
    
    time_wind = VerificaRestricaoTimeWindows(s, dados, debug)
    
    sched = VerificaRestricaoScheduling(s, dados, desloc, debug)
    
    cont = VerificaRestricaoContinuidade(s, debug)
    
    sond = VerificarSondas(s, sondas, debug)
    
    maxfree = VerificaMaxFree(s, max_free, debug)
    
    totfree = VerificaTotalFree(s, total_free, debug)
    
    totsetup = VerificaTotalSetup(s, total_setup, desloc, debug)
    
    if debug:
        tempo_total = timer.get_time(reference = "total", unit = "seconds")
        print ("Tempo gasto verificando restrições: ", tempo_total)
    
    return fo & orc & unic & time_wind & sched & cont & sond & maxfree & totfree & totsetup

def PrintSolution(s):
    n_sondas = len(s.keys())
    print ('solução atual: ')
    for i in range(n_sondas):
        for node in s[i]:
            print ('sonda ', i, ' executa projetos: ', node.data)

def ConstruirRCL(heap=None, alpha=0.5, debug=False):
    
    if (debug):
        print ("Construindo RCL a partir da lista ", heap)
    
    import copy
    import heapq
    
    heap_local = copy.copy(heap)
    
    rcl = []
    ord_data = []
    
    for i in range(len(heap)):
        ord_data.append(heapq.heappop(heap_local))
    
    s_min = ord_data[len(ord_data) - 1][0]
    s_max = ord_data[0][0]
    threshold = s_min + alpha * (s_max - s_min)
    
    for i in range(len(ord_data)):
        if (ord_data[i][0] <= threshold):
            rcl.append(ord_data[i][1])
    
    if (debug):
        print ("RCL resultante: ", rcl)
    
    return rcl

def TentaChegarProjetoAlocadoParaTras(aloc, node, lag, desloc, projeto, sonda, proc, dados, s, 
                                     f, gastos, sondas, max_free, total_free, total_setup,
                                     tam_prev, debug=False):
    
    import math
    import copy
    import numpy as np
    import heapq
    
    if (debug):
        print ("Tentando chegar projeto alocado para tras")
    
    # se posso chegar projeto alocado para trás
    if (node.prev != None):
        if (node.prev.data[0] == -1):

            flag_setup = None
            delta_setup = 0
            # tenho projeto alocado para frente? se sim, calcular mudança de desloc
            if (node.next != None):
                if (node.next.data[0] != -1):
                    flag_setup = 'next'
                    old_setup = desloc[node.data[0] + lag][node.next.data[0] + lag]
                    new_setup = desloc[projeto + lag][node.next.data[0] + lag]
                    delta_setup = old_setup - new_setup
                elif (node.next.next != None):
                    flag_setup = 'next next'
                    old_setup = desloc[node.data[0] + lag][node.next.next.data[0] + lag]
                    new_setup = desloc[projeto + lag][node.next.next.data[0] + lag]
                    delta_setup = old_setup - new_setup

            # quanto seria o setup?
            setup = desloc[node.data[0] + lag][projeto + lag]

            # quanto de espaço é preciso abrir?
            if (flag_setup == 'next'):
                delta_min = (setup + proc) - delta_setup
            elif (flag_setup == 'next next'):
                delta_min = (setup + proc) - (node.next.data[2]-node.next.data[1]+1) - delta_setup
            else:
                delta_min = (setup + proc)

            if (delta_min < 0):
                delta_min = 9999

            # o espaço disponível na janela anterior basta?
            if ( (node.prev.data[2] - node.prev.data[1] + 1) >= delta_min):

                # chegar o projeto alocado para trás é viável, pela sua janela de tempo?
                if (dados[22][node.data[0]] <= node.data[1] - delta_min):

                    # se não há mudança de desloc, ou a mudança é positiva
                    if (delta_setup >= 0):

                        # qual seria inicio e final
                        inicio = node.data[2] - delta_min + 1
                        final = inicio + setup + proc -1

                        # se for viável inserir projeto nessa janela
                        if ((inicio >= dados[22][projeto]) and (final <= dados[23][projeto])):
                            # viável: fazer alterações

                            aloc = True
                            node.data[1] -= delta_min
                            node.data[2] -= delta_min

                            if ( (node.prev.data[2] - node.prev.data[1] + 1) > delta_min):
                                node.prev.data[2] -= delta_min
                            else:
                                s[sonda].remove_node_by_ref(node.prev)

                            if (flag_setup == 'next'):
                                node.next.data[1] += delta_setup
                                s[sonda].add_node_after_node(value_to_add=[projeto, inicio, final], node_ref=node)
                            elif (flag_setup == 'next next'):
                                node.next.next.data[1] += delta_setup
                                node.next.data[2] += delta_setup
                                node.next.data[1] -= delta_min
                                node.next.data[0] = projeto
                            else:
                                s[sonda].add_node_after_node(value_to_add=[projeto, inicio, final], node_ref=node)

                    # senão, se o desloc aumentar, o próximo projeto continua viável
                    else:
                        flag_realoc = None
                        # se aumentar pra trás
                        if (flag_setup == 'next'):
                            if (dados[22][node.next.data[0]] <= node.next.data[1] + delta_setup):
                                flag_realoc = True
                        elif (flag_setup == 'next next'):
                            if (dados[22][node.next.next.data[0]] <= node.next.next.data[1] + delta_setup):
                                flag_realoc = True

                        if (flag_realoc):

                            # qual seria inicio e final
                            inicio = node.data[2] - delta_min + 1
                            final = inicio + setup + proc -1

                            # se for viável inserir projeto nessa janela
                            if ((inicio >= dados[22][projeto]) and (final <= dados[23][projeto])):
                                # viável: fazer alterações

                                aloc = True
                                node.data[1] -= delta_min
                                node.data[2] -= delta_min

                                if ( (node.prev.data[2] - node.prev.data[1] + 1) > delta_min):
                                    node.prev.data[2] -= delta_min
                                else:
                                    s[sonda].remove_node_by_ref(node.prev)

                                if (flag_setup == 'next'):
                                    node.next.data[1] += delta_setup
                                    s[sonda].add_node_after_node(value_to_add=[projeto, inicio, final], node_ref=node)
                                elif (flag_setup == 'next next'):
                                    node.next.next.data[1] += delta_setup
                                    node.next.data[2] += delta_setup
                                    node.next.data[1] -= delta_min
                                    node.next.data[0] = projeto

                        # senão
                        else:
                            # se aumentar pra frente
                            # testar janela
                            if (flag_setup == 'next'):
                                if (node.next.data[2] - delta_setup <= dados[23][node.next.data[0]]):
                                    flag_realoc = True
                            elif (flag_setup == 'next next'):
                                if (node.next.next.data[2] - delta_setup <= dados[23][node.next.next.data[0]]):
                                    flag_realoc = True

                            if (flag_realoc):

                                # testar conflito
                                flag_conflict = None
                                if (flag_setup == 'next'):
                                    if (node.next.next != None):
                                        if (node.next.next.data[0] == -1):
                                            if (-delta_setup <= (node.next.next.data[2]-node.next.next.data[1]+1)):
                                                flag_conflict = True

                                if (flag_setup == 'next next'):
                                    if (node.next.next.next != None):
                                        if (node.next.next.next.data[0] == -1):
                                            if (-delta_setup <= (node.next.next.next.data[2]-node.next.next.next.data[1]+1)):
                                                flag_conflict = True

                                if (flag_conflict):

                                    # qual seria o inicio e final
                                    inicio = node.data[2] - (delta_min + delta_setup) + 1
                                    final = inicio + setup + proc -1

                                    # se for viável inserir projeto nessa janela
                                    if ((inicio >= dados[22][projeto]) and (final <= dados[23][projeto])):
                                        # viável: fazer alterações

                                        aloc = True
                                        node.data[1] -= (delta_min + delta_setup)
                                        node.data[2] -= (delta_min + delta_setup)

                                        if ( (node.prev.data[2] - node.prev.data[1] + 1) > (delta_min + delta_setup)):
                                            node.prev.data[2] -= (delta_min + delta_setup)
                                        else:
                                            s[sonda].remove_node_by_ref(node.prev)

                                        if (flag_setup == 'next'):
                                            node.next.data[2] -= delta_setup

                                            if (-delta_setup < (node.next.next.data[2]-node.next.next.data[1]+1)):
                                                node.next.next.data[1] -= delta_setup
                                            else:
                                                s[sonda].remove_node_by_ref(node.next.next)

                                            s[sonda].add_node_after_node(value_to_add=[projeto, inicio, final], node_ref=node)
                                        elif (flag_setup == 'next next'):
                                            node.next.next.data[2] -= delta_setup

                                            if (-delta_setup < (node.next.next.next.data[2]-node.next.next.next.data[1]+1)):
                                                node.next.next.next.data[1] -= delta_setup
                                            else:
                                                s[sonda].remove_node_by_ref(node.next.next.next)

                                            node.next.data[1] -= (delta_min + delta_setup)
                                            node.next.data[0] = projeto
    
    if (aloc):
        
        # atualizar dados
        gastos += dados[20][projeto]
        heapq.heappush(sondas, ( (tam_prev + (final - inicio + 1 - delta_setup)) , sonda))
        f += dados[19][projeto]
        total_free -= final - inicio + 1 - delta_setup
        total_setup += setup - delta_setup
        max_free = copy.deepcopy(sondas[0][0])
        
        if (debug):
            print ("Sucesso em chegar projeto para trás")
            check = VerificaRestricoes(s, dados, f, gastos, desloc, sondas, max_free, total_free, total_setup, debug)
            if (check):
                check_str = "viável"
            else:
                check_str = "inviável"
            print ("Nova solução ", check_str)
            PrintSolution(s)
        
        return aloc, gastos, sondas, f, total_free, total_setup, max_free
    else:
        if (debug):
            print ("Não foi possível chegar projeto para trás")
        return aloc, gastos, sondas, f, total_free, total_setup, max_free


def TentaChegarProjetoAlocadoParaFrente(aloc, node, lag, desloc, projeto, sonda, proc, dados, s,
                                       f, gastos, sondas, max_free, total_free, total_setup,
                                       tam_prev, debug=False):
    
    import math
    import copy
    import numpy as np
    import heapq
    
    if (debug):
        print ("Tentando chegar projeto alocado para frente")
    
    # se posso chegar projeto para frente
    if (node.next != None):
        if (node.next.data[0] == -1):

            # quanto muda de deslocamento?
            delta_setup = 0
            node_prev = copy.copy(node.prev)
            while (node_prev != None):
                if (node_prev.data[0] != -1):
                    old_setup = desloc[node_prev.data[0] + lag][node.data[0] + lag]
                    new_setup = desloc[projeto + lag][node.data[0] + lag]
                    delta_setup = old_setup - new_setup
                    break
                else:
                    node_prev = node_prev.prev
            if (node_prev == None):
                old_setup = desloc[sonda][node.data[0] + lag]
                new_setup = desloc[projeto + lag][node.data[0] + lag]
                delta_setup = old_setup - new_setup

            # quanto seria o setup?
            node_prev = copy.copy(node.prev)
            while (node_prev != None):
                if (node_prev.data[0] != -1):
                    setup = desloc[node_prev.data[0] + lag][projeto + lag]
                    break
                else:
                    node_prev = node_prev.prev
            if (node_prev == None):
                setup = desloc[sonda][projeto + lag]

            # quanto de espaço é preciso abrir?
            delta_min = (setup + proc)

            # o espaço disponível na janela seguinte basta?
            if ((node.next.data[2] - node.next.data[1] + 1) >= (delta_min - delta_setup)):

                # se for viavel, pela janela de tempo, colocar projeto para frente
                if (node.data[2] + delta_min - delta_setup <= dados[23][node.data[0]]):

                    # qual seria o inicio e o final
                    final = node.data[1] + delta_min -1
                    inicio = final - proc - setup + 1

                    # se for viável inserir projeto nessa janela
                    if ((inicio >= dados[22][projeto]) and (final <= dados[23][projeto])):

                        # viável: fazer alterações
                        aloc = True
                        node.data[1] += delta_min
                        node.data[2] += delta_min - delta_setup

                        if ((node.next.data[2] - node.next.data[1] + 1) > (delta_min - delta_setup)):
                            node.next.data[1] += delta_min - delta_setup
                        else:
                            s[sonda].remove_node_by_ref(node.next)

                        s[sonda].add_node_before_node(value_to_add=[projeto, inicio, final], node_ref=node)
    
    if (aloc):
        
        # atualizar dados
        gastos += dados[20][projeto]
        heapq.heappush(sondas, ( (tam_prev + (final - inicio + 1 - delta_setup)) , sonda))
        f += dados[19][projeto]
        total_free -= final - inicio + 1 - delta_setup
        total_setup += setup - delta_setup
        max_free = copy.deepcopy(sondas[0][0])
        
        if (debug):
            print ("Sucesso em chegar projeto alocado para frente")
            check = VerificaRestricoes(s, dados, f, gastos, desloc, sondas, max_free, total_free, total_setup, debug)
            if (check):
                check_str = "viável"
            else:
                check_str = "inviável"
            print ("Nova solução ", check_str)
            PrintSolution(s)
        
        return aloc, gastos, sondas, f, total_free, total_setup, max_free
    else:
        if (debug):
            print ("Não foi possível chegar projeto alocado para frente")
        return aloc, gastos, sondas, f, total_free, total_setup, max_free


def TentaInserirNodeDeProjeto(s, node, sonda, projeto, dados, lag, desloc, proc, aloc, gastos, 
                              f, sondas, max_free, total_free, total_setup,
                              tam_prev, debug=False):
    
    import math
    import copy
    import numpy as np
    import heapq
    
    if (debug):
        print ("Tentando inserir projeto ", projeto, " no node onde está o projeto ", node.data[0])
    
    # verificar interceção entre projeto alocado e janela do projeto a alocar
    if ((node.data[1] <= dados[23][projeto]) and (node.data[2] >= dados[22][projeto])):
        
        aloc, gastos, sondas, f, total_free, total_setup, max_free = TentaChegarProjetoAlocadoParaTras(aloc, node, lag, desloc, projeto, sonda, proc, dados, s, 
                                     f, gastos, sondas, max_free, total_free, total_setup,
                                     tam_prev, debug)
        
        # se não conseguir chegar para trás
        if (not aloc):
            aloc, gastos, sondas, f, total_free, total_setup, max_free = TentaChegarProjetoAlocadoParaFrente(aloc, node, lag, desloc, projeto, sonda, proc, dados, s,
                                       f, gastos, sondas, max_free, total_free, total_setup,
                                       tam_prev, debug)
    
    if (aloc):
        if (debug):
            print ("Sucesso em inserir projeto")
        return aloc, gastos, sondas, f, total_free, total_setup, max_free
    else:
        if (debug):
            print ("Não foi possível inserir projeto")
        return aloc, gastos, sondas, f, total_free, total_setup, max_free


def TentaColocarDiffParaFrente(aloc, node, projeto, s, sonda, dados, setup, delta_setup, inicio, final,
                              f, gastos, desloc, sondas, max_free, total_free, total_setup,
                              tam_prev, debug=False):
    
    import math
    import copy
    import numpy as np
    import heapq
    
    if (debug):
        print ("Tentando colocar diferenteça de setup para frente")
    
    # posso aumentar a due do projeto que sofre modificação do deslocamento?
    # testar sua janela de tempo (viabilidade)
    flag_tw = 'inviavel'
    if (node.next.data[2] - delta_setup <= dados[23][node.next.data[0]]):
        flag_tw = 'viavel'
    # testar conflito com projeto next
    flag_conflict = 'inviavel'
    if (node.next.next != None):
        if (node.next.next.data[0] == -1):
            if (-delta_setup <= (node.next.next.data[2]-node.next.next.data[1]+1)):
                flag_conflict = 'viavel'

    # ações para cada combinação de flag e marcar flag aloc
    # se não tem problema de janela nem conflito, segue o jogo
    if ((flag_tw == 'viavel') and (flag_conflict == 'viavel')):

        node.next.data[2] -= delta_setup
        if (node.next.next != None):
            if (-delta_setup < (node.next.next.data[2]-node.next.next.data[1]+1)):
                node.next.next.data[1] -= delta_setup
            else:
                s[sonda].remove_node_by_ref(node.next.next)
        aloc = True

    # senão, se não tem problema de janela, mas tem de conflito
    elif ((flag_tw == 'viavel') and (flag_conflict == 'inviavel')):
        # teria que tentar postergar projeto next next
        if (node.next.next != None):
            if (node.next.next.next != None):
                if (node.next.next.next.data[0] == -1):
                    if (-delta_setup <= (node.next.next.next.data[2]-node.next.next.next.data[1]+1)):
                        if (node.next.next.data[2] - delta_setup <= dados[23][node.next.next.data[0]]):

                            if (-delta_setup < (node.next.next.next.data[2]-node.next.next.next.data[1]+1)):
                                node.next.next.next.data[1] -= delta_setup
                            else:
                                s[sonda].remove_node_by_ref(node.next.next.next)

                            node.next.next.data[2] -= delta_setup
                            node.next.next.data[1] -= delta_setup
                            node.next.data[2] -= delta_setup
                            aloc = True
    
    if (aloc):
        
        # atualizar dados
        gastos += dados[20][projeto]
        heapq.heappush(sondas, ( (tam_prev + (final - inicio + 1 - delta_setup)) , sonda))
        f += dados[19][projeto]
        total_free -= final - inicio + 1 - delta_setup
        total_setup += setup - delta_setup
        max_free = copy.deepcopy(sondas[0][0])
        
        if (debug):
            print ("Sucesso ao colocar diferenteça de setup para frente")
        
    elif (debug):
        print ("Não foi possível colocar diferença de setup para frente")
    
    return aloc, gastos, sondas, f, total_free, total_setup, max_free

def TentaColocarDiffParaTras(aloc, node, projeto, s, sonda, dados, setup, delta_setup, inicio, final,
                            f, gastos, desloc, sondas, max_free, total_free, total_setup,
                            tam_prev, debug=False):
    
    import math
    import copy
    import numpy as np
    import heapq
    
    if (debug):
        print ("Tentando colocar diferença de setup para tras")
    
    # posso reduzir a release do projeto que sofre modificação do deslocamento? 
    # testar sua janela de tempo (viabilidade)
    flag_tw = 'inviavel'
    if (node.next.data[1] + delta_setup >= dados[22][node.next.data[0]]):
        flag_tw = 'viavel'
    flag_conflict = 'inviavel'
    # testar conflito com projeto a ser inserido
    if (node.next.data[1] + delta_setup > final):
        flag_conflict = 'viavel'

    # ações para cada combinação de flag e marcar flag aloc
    # se não tem problema de janela nem de conflito, segue o jogo
    if ((flag_tw=='viavel') and (flag_conflict=='viavel')):

        node.next.data[1] += delta_setup
        node.data[2] += delta_setup
        aloc = True

    # senão, se não tem problema de janela, mas tem conflito
    elif ((flag_tw=='viavel') and (flag_conflict=='inviavel')):
        # teria que alterar inicio e final do projeto a ser inserido
        # se continua dentro da janela 
        if (inicio+delta_setup >= node.data[1]):
            # e é viável pela janela de tempo
            if (inicio+delta_setup >= dados[22][node.data[0]]):

                inicio += delta_setup
                final += delta_setup
                node.next.data[1] += delta_setup
                node.data[2] += delta_setup
                aloc = True
        
        # senão, se é viável pela janela de tempo
        elif (inicio+delta_setup >= dados[22][node.data[0]]):
            # e consigo antecipar o prev
            if (node.prev != None):
                if (node.prev.prev != None):
                    if (node.prev.prev.data[0] == -1):
                        # quanto consigo antecipar o prev?
                        delta_prev = node.prev.data[1] - max(node.prev.prev.data[1], dados[22][node.prev.data[0]])
                        delta_prev = max(0, delta_prev)
                        # se é suficiente
                        if (delta_prev >= -delta_setup):

                            if (-delta_setup < (node.prev.prev.data[2]-node.prev.prev.data[1]+1)):
                                node.prev.prev.data[2] += delta_setup
                            else:
                                s[sonda].remove_node_by_ref(node.prev.prev)

                            node.prev.data[1] += delta_setup
                            node.prev.data[2] += delta_setup

                            inicio += delta_setup
                            final += delta_setup
                            node.next.data[1] += delta_setup
                            node.data[2] += delta_setup
                            aloc = True
    
    if (aloc):
        
        # atualiza dados
        gastos += dados[20][projeto]
        heapq.heappush(sondas, ( (tam_prev + (final - inicio + 1 - delta_setup)) , sonda))
        f += dados[19][projeto]
        total_free -= final - inicio + 1 - delta_setup
        total_setup += setup - delta_setup
        max_free = copy.deepcopy(sondas[0][0])
        
        if (debug):
            print ("Sucesso ao colocar diferenteça de setup para tras")
        return aloc, gastos, sondas, f, total_free, total_setup, max_free
    else:
        if (debug):
            print ("Não foi possível colocar diferenteça de setup para tras")
        return aloc, gastos, sondas, f, total_free, total_setup, max_free

def AtualizaListaDeAtividades(aloc, node, s, projeto, sonda, inicio, final,
                             dados, f, gastos, desloc, sondas, max_free, total_free, total_setup,
                             tam_prev, debug=False):
    
    import math
    import copy
    import numpy as np
    import heapq
    
    if (debug):
        print ("Atualizando lista de atividades")
    
    # se projeto preenche janela toda
    if ( (int(node.data[1])==int(inicio)) and (int(node.data[2])==int(final)) ):

        # substituir janela pela alocação do projeto
        node.data = [copy.copy(projeto), inicio, final]

    # senão, se projeto preenche início da janela    
    elif (int(node.data[1])==int(inicio)):

        # atualizar release da janela
        node.data[1] = final + 1

        # inserir projeto antes da janela
        s[sonda].add_node_before_node(value_to_add=[projeto, inicio, final], node_ref=node)

    # senão, se projeto preenche final da janela
    elif (int(node.data[2])==int(final)):

        # atualiza a due da janela
        node.data[2] = inicio - 1

        # inserir projeto depois da janela
        s[sonda].add_node_after_node(value_to_add=[projeto, inicio, final], node_ref=node)

    # senão, se projeto preenche o meio da janela
    else:

        # atualiza release da janela
        temp = copy.copy(node.data[1])
        node.data[1] = final + 1

        # insere janela nova antes da janela original
        s[sonda].add_node_before_node(value_to_add=[-1, temp, inicio - 1], node_ref=node)

        # insere projeto antes da janela original
        s[sonda].add_node_before_node(value_to_add=[projeto, inicio, final], node_ref=node)
    
    if (debug):
        print ("Lista de atividades atualizada")
        
        check = VerificaRestricoes(s, dados, f, gastos, desloc, sondas, max_free, total_free, total_setup, debug)
        if (check):
            check_str = "viável"
        else:
            check_str = "inviável"
        print ("Nova solução ", check_str)
        PrintSolution(s)

def TentaRealocarProjetosVizinhos(aloc, node, s, projeto, sonda, dados, proc, setup, delta_setup,
                                 f, gastos, desloc, sondas, max_free, total_free, total_setup,
                                 tam_prev, debug=False):
    
    import math
    import copy
    import numpy as np
    import heapq
    
    if (debug):
        print ("Tentando realocar projetos vizinhos")
    
    # verificar se janela da sonda tem interceção com janela do projeto
    if ((node.data[1] <= dados[23][projeto]) and (node.data[2] >= dados[22][projeto])):

        # consigo antecipar o prev? quanto?
        delta_prev = 0
        if node.prev == None:
            delta_prev = 0
        elif node.prev.prev == None:
            delta_prev = 0
        else:
            if node.prev.prev.data[0] != -1:
                delta_prev = 0
            else:
                delta_prev = node.prev.data[1] - max(node.prev.prev.data[1], dados[22][node.prev.data[0]])
                delta_prev = max(0, delta_prev)

        # consigo postergar o next? quanto?
        delta_next = 0
        if node.next == None:
            delta_next = 0
        elif node.next.next == None:
            delta_next = 0
        else:
            if node.next.next.data[0] != -1:
                delta_next = 0
            else:
                delta_next = min(node.next.next.data[2], dados[23][node.next.data[0]]) - node.next.data[2]
                delta_next = max(0, delta_next)

        # quanto de delta eu preciso?
        delta_min = (setup + proc) - (node.data[2] - node.data[1] + 1) - delta_setup

        # só com antecipação do prev, torna viável?
        if (delta_prev >= delta_min):
            # se contempla janela
            if ((node.data[1]-delta_min>=dados[22][projeto]) and (node.data[2]+delta_setup<=dados[23][projeto])):
                flag_realoc = 'viavel'
                # se há mudança de setup para mais
                if (delta_setup < 0):
                    # checar viabilidade de diminuir release do next
                    if (node.next.data[1] + delta_setup < dados[22][node.next.data[0]]):
                        flag_realoc = 'inviavel'
                if (flag_realoc == 'viavel'):
                    # fazer antecipação do prev
                    node.prev.data[1] -= delta_min
                    node.prev.data[2] -= delta_min

                    if (node.prev.prev.data[2] - delta_min < node.prev.prev.data[1]):
                        s[sonda].remove_node_by_ref(node.prev.prev)
                    else:
                        node.prev.prev.data[2] -= delta_min

                    aloc = True
                    node.data[1] -= delta_min

        # só com postergação do next, torna viável?
        elif (delta_next >= delta_min):
            # se contempla janela
            if ((node.data[1]>=dados[22][projeto]) and (node.data[2]+delta_min+delta_setup<=dados[23][projeto])):
                flag_realoc = 'viavel'
                # se há mudança de setup para mais
                if (delta_setup < 0):
                    # checar viabilidade de diminuir release do next
                    if (node.next.data[1] + delta_setup < dados[22][node.next.data[0]]):
                        flag_realoc = 'inviavel'
                if (flag_realoc == 'viavel'):
                    # fazer postergação do next
                    node.next.data[1] += delta_min
                    node.next.data[2] += delta_min

                    if (node.next.next.data[1] + delta_min > node.next.next.data[2]):
                        s[sonda].remove_node_by_ref(node.next.next)
                    else:
                        node.next.next.data[1] += delta_min

                    aloc = True
                    node.data[2] += delta_min

        # somando antecipação do prev e postergação do next, torna viável?
        elif (delta_prev + delta_next >= delta_min):
            # se, antecipando prev primeiro, contempla janela
            if ((node.data[1]-delta_prev>=dados[22][projeto]) and (node.data[2]+delta_setup+(delta_min - delta_prev)<=dados[23][projeto])):
                flag_realoc = 'viavel'
                # se há mudança de setup
                if (delta_setup < 0):
                    # checar viabilidade de diminuir release do next
                    if (node.next.data[1] + delta_setup < dados[22][node.next.data[0]]):
                        flag_realoc = 'inviavel'
                if (flag_realoc == 'viavel'):
                    # fazer antecipação do prev primeiro
                    node.prev.data[1] -= delta_prev
                    node.prev.data[2] -= delta_prev

                    if (node.prev.prev.data[2] - delta_prev < node.prev.prev.data[1]):
                        s[sonda].remove_node_by_ref(node.prev.prev)
                    else:
                        node.prev.prev.data[2] -= delta_prev

                    node.data[1] -= delta_prev
                    # fazer postergação do next depois
                    node.next.data[1] += (delta_min - delta_prev)
                    node.next.data[2] += (delta_min - delta_prev)

                    if (node.next.next.data[1] + (delta_min - delta_prev) > node.next.next.data[2]):
                        s[sonda].remove_node_by_ref(node.next.next)
                    else:
                        node.next.next.data[1] += (delta_min - delta_prev)

                    aloc = True
                    node.data[2] += (delta_min - delta_prev)

            # senão, se, postergando nexto primeiro, contempla janela
            elif ((node.data[1]-(delta_min - delta_next)>=dados[22][projeto]) and (node.data[2]+delta_setup+delta_next<=dados[23][projeto])):
                flag_realoc = 'viavel'
                # se há mudança de setup
                if (delta_setup < 0):
                    # checar viabilidade de diminuir release do next
                    if (node.next.data[1] + delta_setup < dados[22][node.next.data[0]]):
                        flag_realoc = 'inviavel'
                if (flag_realoc == 'viavel'):
                    # fazer postergação do next primeiro
                    node.next.data[1] += delta_next
                    node.next.data[2] += delta_next

                    if (node.next.next.data[1] + delta_next > node.next.next.data[2]):
                        s[sonda].remove_node_by_ref(node.next.next)
                    else:
                        node.next.next.data[1] += delta_next

                    node.data[2] += delta_next
                    # fazer antecipação do prev depois
                    node.prev.data[1] -= (delta_min - delta_next)
                    node.prev.data[2] -= (delta_min - delta_next)

                    if (node.prev.prev.data[2] - (delta_min - delta_next) < node.prev.prev.data[1]):
                        s[sonda].remove_node_by_ref(node.prev.prev)
                    else:
                        node.prev.prev.data[2] -= (delta_min - delta_next)

                    aloc = True
                    node.data[1] -= (delta_min - delta_next)
    if aloc:
        
        # atualiza release do next e due da janela, caso o setup tenha sido alterado
        if delta_setup != 0:
            node.next.data[1] += delta_setup
            node.data[2] += delta_setup

        inicio = node.data[1]
        final = node.data[2]

        node.data[0] = projeto
    
    if (aloc):
        
        # atualiza metricas
        gastos += dados[20][projeto]
        heapq.heappush(sondas, ( (tam_prev + (final - inicio + 1 - delta_setup)) , sonda))
        f += dados[19][projeto]
        total_free -= final - inicio + 1 - delta_setup
        total_setup += setup - delta_setup
        max_free = copy.deepcopy(sondas[0][0])
        
        if (debug):
            print ("Sucesso ao realocar projetos vizinhos")
            check = VerificaRestricoes(s, dados, f, gastos, desloc, sondas, max_free, total_free, total_setup, debug)
            if (check):
                check_str = "viável"
            else:
                check_str = "inviável"
            print ("Nova solução ", check_str)
            PrintSolution(s)
        
        return aloc, gastos, sondas, f, total_free, total_setup, max_free
    else:
        if (debug):
            print ("Não foi possível realocar projetos vizinhos")
        return aloc, gastos, sondas, f, total_free, total_setup, max_free

def TentaInserirNodeDeJanela(s, node, sonda, projeto, dados, lag, desloc, proc, aloc, gastos,
                            sondas, f, max_free, total_free, total_setup, tam_prev, debug=False):
    
    import math
    import copy
    import numpy as np
    import heapq
    
    if (debug):
        print ("Tentando inserir projeto ", projeto, " em node de janela")
    
    # busca tempo de deslocamento / setup 
    # se node for head, considerar origem da sonda
    if node.prev == None:
        prev = sonda
    # senão, considerar projeto anterior
    else:
        prev = node.prev.data[0] + lag
    setup = desloc[prev][projeto + lag]
    
    # se existe projeto alocado após a janela atual, o setup para ele vai mudar quanto?
    if node.next != None:
        old_setup = desloc[prev][node.next.data[0] + lag]
        new_setup = desloc[projeto + lag][node.next.data[0] + lag]
        delta_setup = old_setup - new_setup
    else:
        delta_setup = 0
    
    # calcula o mínimo tempo de início e o máximo tempo de término do projeto dentro da janela
    release = max(node.data[1], dados[22][projeto])
    due = min(node.data[2] + delta_setup, dados[23][projeto])

    # se consigo colocar o projeto dentro da janela
    if (release + proc + setup -1 <= due):

        # escolher tempo de inicio para alocar projeto
        delta1 = max((release - node.data[1]), (due - release) - (proc + setup) + (node.data[2] - due))
        delta2 = max((node.data[2] - due), (due - release) - (proc + setup) + (release - node.data[1]))
        if (delta1 >= delta2):
            inicio = copy.copy(release)
            final = copy.copy(release + setup + proc - 1)
        else:
            inicio = copy.copy(due - proc - setup + 1)
            final = copy.copy(due)

        # atualiza release do next e due da janela, caso o setup tenha sido alterado
        if delta_setup == 0:
            
            if (debug):
                print ("Inserindo sem realocações: delta_setup = 0")
            
            aloc = True
            
            gastos += dados[20][projeto]
            heapq.heappush(sondas, ( (tam_prev + (final - inicio + 1 - delta_setup)) , sonda))
            f += dados[19][projeto]
            total_free -= final - inicio + 1 - delta_setup
            total_setup += setup - delta_setup
            max_free = copy.deepcopy(sondas[0][0])
            
        else:
            # se for reduzir o deslocamento, não tem problema de viabilidade nem conflito
            if (delta_setup > 0):
                if (node.next.data[2] > node.next.data[1]):
                    
                    if (debug):
                        print ("Inserindo sem realocações: delta_setup > 0")

                    node.next.data[1] += delta_setup
                    node.data[2] += delta_setup
                    
                    aloc = True
                    
                    gastos += dados[20][projeto]
                    heapq.heappush(sondas, ( (tam_prev + (final - inicio + 1 - delta_setup)) , sonda))
                    f += dados[19][projeto]
                    total_free -= final - inicio + 1 - delta_setup
                    total_setup += setup - delta_setup
                    max_free = copy.deepcopy(sondas[0][0])
            
            # se for aumentar, tentar primeiro colocar diferença pra trás
            elif (delta_setup < 0):
                aloc, gastos, sondas, f, total_free, total_setup, max_free = TentaColocarDiffParaTras(aloc, node, projeto, s, sonda, dados, setup, delta_setup, inicio, final,
                            f, gastos, desloc, sondas, max_free, total_free, total_setup,
                            tam_prev, debug)
                
                # se ainda não foi alocado, tentar colocar diferença para frente
                if (not aloc):
                    aloc, gastos, sondas, f, total_free, total_setup, max_free = TentaColocarDiffParaFrente(aloc, node, projeto, s, sonda, dados, setup, delta_setup, inicio, final,
                              f, gastos, desloc, sondas, max_free, total_free, total_setup,
                              tam_prev, debug)
        
        if (aloc):
            # atualizando a lista de atividades
            AtualizaListaDeAtividades(aloc, node, s, projeto, sonda, inicio, final,
                             dados, f, gastos, desloc, sondas, max_free, total_free, total_setup,
                             tam_prev, debug)
            
    else:
        # senão, tentar realocar projetos
        aloc, gastos, sondas, f, total_free, total_setup, max_free = TentaRealocarProjetosVizinhos(aloc, node, s, projeto, sonda, dados, proc, setup, delta_setup,
                                 f, gastos, desloc, sondas, max_free, total_free, total_setup,
                                 tam_prev, debug)
    
    if (aloc):
        if (debug):
            print ("Sucesso ao inserir o projeto")
        return aloc, gastos, sondas, f, total_free, total_setup, max_free
    else:
        if (debug):
            print ("Não foi possível inserir o projeto")
        return aloc, gastos, sondas, f, total_free, total_setup, max_free

def ConstruirSolucao(dados, n_projetos, n_sondas, n_periodos, custo_total, desloc, 
                     criterio='lucro/custo', alpha=0.5, s=None, debug=False):
    
    import math
    import copy
    import numpy as np
    import heapq
    import CPUtimer
    
    if debug:
        print ("Construindo solução")
    
    timer = CPUtimer.CPUTimer()
    timer.reset()
    timer.start()
    
    lag = n_sondas
    
    # inicializa conjunto de projetos já selecionados
    proj_usados = set()
    
    # inicializa contador de gastos total
    gastos = 0
    
    # conjunto de sondas é representado com uma Heap
    sondas = []
    sondas_final = []
    sondas_set = set()
    
    # inicializa valor da função objetivo da solução
    fitness = 0
    
    # inicializando solução
    if (s == None):
        
        if (debug):
            print ("Sem solução inicial fornecida")
        
        s = {i:DoublyLinkedList(nodes=[[-1, 0, n_periodos]]) for i in range(n_sondas)}
        sondas = [(-(n_periodos+1), i) for i in range(n_sondas)]
        for i in range(n_sondas):
            sondas_set.add(i)
        
        total_setup = 0
        total_free = (n_periodos + 1) * n_sondas
        max_free = - (n_periodos + 1)
        
    else:
        
        total_setup = 0
        total_free = 0
        max_free = 0
        
        for sonda in range(n_sondas):
            temp = n_periodos + 1
            prev = None
            for node in s[sonda]:
                if (node.data[0] != -1):
                    proj_usados.add(node.data[0])
                    gastos += dados[20][node.data[0]]
                    fitness += dados[19][node.data[0]]
                    temp -= node.data[2] - node.data[1] + 1
                    if (prev == None):
                        total_setup += desloc[sonda][node.data[0] + lag]
                        prev = node.data[0]
                    else:
                        total_setup += desloc[prev + lag][node.data[0] + lag]
                        prev = node.data[0]
            if (-temp < max_free):
                max_free = -temp
            
            sondas.append((-temp, sonda))
            total_free += temp
            
        heapq.heapify(sondas)
        
        if (debug):
            check = VerificaRestricoes(s, dados, fitness, gastos, desloc, sondas, max_free, total_free, total_setup, debug)
            if (check):
                check_str = "viável"
            else:
                check_str = "inviável"
            print ("Solução inicial fornecida com fitness=", fitness, " e gastos=", gastos, " sendo ", check_str)
    
    # inicializando lista de candidatos, por sonda
    s_candidatos = {i:[] for i in range(n_sondas)}
    
    # armazena lista de candidatos como uma heap, dependendo do critério guloso
    for i in range(n_sondas):
        for j in range(n_projetos):
            
            if (j in proj_usados):
                continue
            else:
                sondas_set.add(i)
            
            if (criterio == 'lucro'):
                criterio_val = dados[19][j]
                heapq.heappush( s_candidatos[i], (-criterio_val, j) )
            elif (criterio == 'lucro/custo'):
                criterio_val = dados[19][j] / dados[20][j]
                heapq.heappush( s_candidatos[i], (-criterio_val, j) )
            elif (criterio == 'lucro/duracao'):
                criterio_val = dados[19][j] / (dados[21][j]+1)
                heapq.heappush( s_candidatos[i], (-criterio_val, j) )
            elif (criterio == 'custo'):
                criterio_val = dados[20][j]
                heapq.heappush( s_candidatos[i], (criterio_val, j) )
            elif (criterio == 'duracao'):
                criterio_val = dados[21][j]
                heapq.heappush( s_candidatos[i], (criterio_val, j) )
            elif (criterio == 'janela'):
                criterio_val = dados[23][j] / dados[23][j]
                heapq.heappush( s_candidatos[i], (-criterio_val, j) )
    
    # enquanto nenhuma restrição for alcançada
    while (gastos < custo_total and sondas_set):
        
        if (debug):
            print ("Próxima iteração.")
            print ("sondas =", sondas)
        
        # escolher uma sonda
        rcl = ConstruirRCL(heap=sondas, alpha=alpha, debug=debug)
        sonda = np.random.choice(rcl)
        tam_prev = [v for (v,k) in sondas if (k==sonda)][0]
        sondas.remove((tam_prev, sonda))
        heapq.heapify(sondas)
        
        # escolher um projeto
        rcl = ConstruirRCL(heap=s_candidatos[sonda], alpha=alpha, debug=debug)
        projeto = np.random.choice(rcl)
        val = [v for (v,k) in s_candidatos[sonda] if (k==projeto)][0]
        s_candidatos[sonda].remove((val, projeto))
        heapq.heapify(s_candidatos[sonda])
        
        # se valor do projeto não aumenta a função objetivo, pular
        if (dados[19][projeto] <= 0.):
            if (s_candidatos[sonda] == []):
                heapq.heappush(sondas_final, (tam_prev, sonda))
                if (sonda in sondas_set):
                    sondas_set.remove(sonda)
                continue
            else:
                heapq.heappush(sondas, (tam_prev, sonda))
                continue
        
        # se projeto já foi escolhido, pular
        if (projeto in proj_usados):
            if (s_candidatos[sonda] == []):
                heapq.heappush(sondas_final, (tam_prev, sonda))
                if (sonda in sondas_set):
                    sondas_set.remove(sonda)
                continue
            else:
                heapq.heappush(sondas, (tam_prev, sonda))
                continue
        
        # se executar o projeto excede limite de gastos, pular
        if (gastos + dados[20][projeto] > custo_total):
            if (s_candidatos[sonda] == []):
                heapq.heappush(sondas_final, (tam_prev, sonda))
                if (sonda in sondas_set):
                    sondas_set.remove(sonda)
                continue
            else:
                heapq.heappush(sondas, (tam_prev, sonda))
                continue
        
        aloc = False
        proc = dados[21][projeto]
        
        # percorre atividades da sonda para ver se existe janela disponível na sonda
        for i, node in enumerate(s[sonda]):
            
            # se node não for de janela de tempo (é de projeto)
            if (node.data[0] != -1):
                
                aloc, gastos, sondas, fitness, total_free, total_setup, max_free = TentaInserirNodeDeProjeto(s, node, sonda, projeto, dados, lag, desloc, proc, aloc, gastos, 
                              fitness, sondas, max_free, total_free, total_setup,
                              tam_prev, debug)
                
                if (aloc):
                    proj_usados.add(copy.copy(projeto))
                    break
            
            # se node for de janela de tempo
            if (node.data[0] == -1):
                
                aloc, gastos, sondas, fitness, total_free, total_setup, max_free = TentaInserirNodeDeJanela(s, node, sonda, projeto, dados, lag, desloc, proc, aloc, gastos,
                            sondas, fitness, max_free, total_free, total_setup, 
                            tam_prev, debug)
                
                if (aloc):
                    proj_usados.add(copy.copy(projeto))
                    break
        
        if (aloc):
            if (s_candidatos[sonda] == []):
                tam_prev = [v for (v,k) in sondas if (k==sonda)][0]
                sondas.remove((tam_prev, sonda))
                heapq.heapify(sondas)
                heapq.heappush(sondas_final, (tam_prev, sonda))
                if (sonda in sondas_set):
                    sondas_set.remove(sonda)
        else:
            if (s_candidatos[sonda] == []):
                heapq.heappush(sondas_final, (tam_prev, sonda))
                if (sonda in sondas_set):
                    sondas_set.remove(sonda)
            else:
                heapq.heappush(sondas, (tam_prev, sonda))
    
    while (sondas):
        (key, val) = heapq.heappop(sondas)
        heapq.heappush(sondas_final, (key, val))
    
    heapq.heapify(sondas_final)
    max_free = sondas_final[0][0]
    
    tempo_total = timer.get_time(reference = "total", unit = "seconds")
    
    if (debug):
        print ("Solução construída!")
        print ("Com fitness, ", fitness)
        print ("Com gastos, ", gastos)
        print ("Com total free, ", total_free)
        print ("Com max free, ", max_free)
        print ("Com total setup, ", total_setup)
        print ("E sondas=", sondas_final)
        PrintSolution(s)
        print ("Tempo gasto na heurística de construção: ", tempo_total)
    
    return fitness, gastos, s, s_candidatos, sondas_final, total_free, total_setup, max_free, tempo_total

def RodarHeuristica(arquivo, criterio='lucro/custo', alpha=0.5, print_sol=True, debug=False):
    
    """
    Documentação:
    """
    
    import CPUtimer
    import copy
    
    n_projetos, n_sondas, n_periodos, t_init, t_final, delta_t, custo_total, dados, desloc = Read_data(path=arquivo)
    
    timer = CPUtimer.CPUTimer()
    timer.reset()
    timer.start()
    
    f, gastos , s, s_candidatos, sondas, total_free, total_setup, max_free, _ = ConstruirSolucao(dados, 
                                                                           n_projetos, n_sondas, 
                                                                           n_periodos, custo_total, desloc,
                                                                           criterio=criterio, alpha=alpha,
                                                                                             debug=debug)
    
    check = VerificaRestricoes(s, dados, f, gastos, desloc, sondas, max_free, total_free, total_setup, debug)
    
    tempo_total = timer.get_time(reference = "total", unit = "seconds")
    tempo_medio = timer.get_time(reference = "average", unit = "seconds")
    
    if check:
        check_str = 'feasible'
    else:
        check_str = 'not feasible'
    
    if print_sol:
        print (check_str)
        print ('fitness: ', f)
        print ('gastos: ', gastos)
        print ('tempo total de execução (segundos) : ', tempo_total)
        print ('tempo médio de execução (segundos) ', tempo_medio)
        for i in range(n_sondas):
            for node in s[i]:
                print ('sonda ', i, ' executa projetos: ', node.data)
    
    return f, gastos, s, tempo_total, tempo_medio, check_str

def MultStart_Heuristic(arquivo, n_iter=100, criterios=None, alpha=0.5, print_sol=True, debug=False):
    
    """
    Documentação:
    """
    
    import CPUtimer
    import copy
    import numpy as np
    
    print ("Rodando multistart heuristic...")
    
    if criterios == None:
        criterios = ['lucro', 'lucro/custo', 'lucro/duracao', 'custo', 'duracao', 'janela']
    
    n_projetos, n_sondas, n_periodos, t_init, t_final, delta_t, custo_total, dados, desloc = Read_data(path=arquivo)
    
    criterio = np.random.choice(criterios)
    
    f, gastos , s, s_candidatos, sondas, total_free, total_setup, max_free, _ = ConstruirSolucao(dados, 
                                                                           n_projetos, n_sondas, 
                                                                           n_periodos, custo_total, desloc,
                                                                           criterio=criterio, alpha=alpha,
                                                                                             debug=debug)
    
    best_f = copy.deepcopy(f)
    best_gastos = copy.deepcopy(gastos)
    best_s = copy.deepcopy(s)
    best_total_free = copy.deepcopy(total_free)
    best_total_setup = copy.deepcopy(total_setup)
    best_max_free = copy.deepcopy(max_free)
    best_sondas = copy.deepcopy(sondas)
    
    timer = CPUtimer.CPUTimer()
    timer.reset()
    timer.start()
    
    i = 1
    while(n_iter >= i):
        
        # print ("iteração: ", i)
        
        i += 1
        
        criterio = np.random.choice(criterios)
        
        alpha = np.random.choice([0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.85, 0.9, 0.95, 0.99])
        
        f, gastos , s, _, sondas, total_free, total_setup, max_free, _ = ConstruirSolucao(dados, n_projetos, n_sondas, 
                                                                               n_periodos, custo_total, desloc,
                                                                               criterio=criterio, alpha=alpha,
                                                                                      debug=debug)
        
        if (f > best_f):
            best_f = copy.deepcopy(f)
            best_gastos = copy.deepcopy(gastos)
            best_s = copy.deepcopy(s)
            best_total_free = copy.deepcopy(total_free)
            best_total_setup = copy.deepcopy(total_setup)
            best_max_free = copy.deepcopy(max_free)
            best_sondas = copy.deepcopy(sondas)
    
    check = VerificaRestricoes(best_s, dados, best_f, best_gastos, desloc, best_sondas, 
                               best_max_free, best_total_free, best_total_setup, debug)
    
    tempo_total = timer.get_time(reference = "total", unit = "seconds")
    tempo_medio = timer.get_time(reference = "average", unit = "seconds")
    
    print ("Multistart heuristic finalizado.")
    
    if check:
        check_str = 'feasible'
    else:
        check_str = 'not feasible'
    
    if print_sol:
        print (check_str)
        print ('fitness: ', best_f)
        print ('gastos: ', best_gastos)
        print ('tempo total de execução (segundos) : ', tempo_total)
        print ('tempo médio de execução (segundos) ', tempo_medio)
        for i in range(n_sondas):
            for node in best_s[i]:
                print ('sonda ', i, ' executa projetos: ', node.data)
    
    return best_f, best_gastos, best_s, tempo_total, tempo_medio, check_str

def VerificarSetupRemovendoNodeProjeto(s, sonda, node, desloc):
    
    lag = len(s.keys())
    
    delta_setup = 0
    setup = 0
    
    prev = node.prev
    while (prev != None):
        if (prev.data[0] != -1):
            break
        else:
            prev = prev.prev
    
    next_node = node.next
    while (next_node != None):
        if (next_node.data[0] != -1):
            break
        else:
            next_node = next_node.next
    
    if (next_node == None):
        if (prev == None):
            setup = desloc[sonda][node.data[0] + lag]
        elif (prev.data[0] == -1):
            setup = desloc[sonda][node.data[0] + lag]
        else:
            setup = desloc[prev.data[0] + lag][node.data[0] + lag]
        return s, 0, setup
    elif (next_node.data[0] == -1):
        if (prev == None):
            setup = desloc[sonda][node.data[0] + lag]
        elif (prev.data[0] == -1):
            setup = desloc[sonda][node.data[0] + lag]
        else:
            setup = desloc[prev.data[0] + lag][node.data[0] + lag]
        return s, 0, setup
    else:
        old_setup = 0
        new_setup = 0
        if (prev == None):
            old_setup = desloc[node.data[0] + lag][next_node.data[0] + lag]
            new_setup = desloc[sonda][next_node.data[0] + lag]
            setup = desloc[sonda][node.data[0] + lag]
        elif (prev.data[0] == -1):
            old_setup = desloc[node.data[0] + lag][next_node.data[0] + lag]
            new_setup = desloc[sonda][next_node.data[0] + lag]
            setup = desloc[sonda][node.data[0] + lag]
        else:
            old_setup = desloc[node.data[0] + lag][next_node.data[0] + lag]
            new_setup = desloc[prev.data[0] + lag][next_node.data[0] + lag]
            setup = desloc[prev.data[0] + lag][node.data[0] + lag]
        
        delta_setup = new_setup - old_setup

        return s, delta_setup, setup


def DesalocarProjetoPorNode(s, projeto, node, sonda, desloc, dados, gastos, sondas,
                            f, max_free, total_free, total_setup, debug=False):
    
    import copy
    import heapq
    
    if (debug):
        print ("Tentando desalocar projeto ", projeto, " da sonda ", sonda)
    
    node_janela = None
    
    # se for único node
    if ((node.prev == None) and (node.next == None)):
        
        if (debug):
            print ("Projeto está no único node da solução")
        
        # criar janela
        node.data[0] = -1
        node_janela = node
    
    # senão
    else:
        
        # se for primeiro node
        if (node.prev == None):
            
            # e tem janela depois
            if (node.next.data[0] == -1):
                
                if (debug):
                    print ("Projeto está no primeiro node e tem janela em seguida")
                
                # verificar se modifica setup 
                s, delta_setup, setup = VerificarSetupRemovendoNodeProjeto(s, sonda, node, desloc)
                
                proc = dados[21][projeto]
                
                # unir com janela
                
                if (delta_setup == 0):
                    
                    if (debug):
                        print ("delta setup = 0")
                    
                    node.next.data[1] = node.data[1]
                    node_janela = node.next
                elif (delta_setup < 0):
                    
                    if (debug):
                        print ("delta setup < 0 : libera espaço")
                    
                    node.next.data[1] = node.data[1]
                    node.next.data[2] += -(delta_setup)
                    node.next.next.data[1] += -(delta_setup)
                    node_janela = node.next
                elif (delta_setup > 0):
                    
                    if (debug):
                        print ("delta setup > 0 : consome espaço")
                    
                    if (node.next.next.data[1] - delta_setup < dados[22][node.next.next.data[0]]):
                        if (debug):
                            print ("Não foi possível desalocar o projeto. Janela inviável.")
                        return s, False, node_janela, gastos, sondas, f, max_free, total_free, total_setup
                    
                    # se delta setup consome mais do que a janela
                    if ((node.data[1] - (node.next.data[2] - delta_setup)) > 1):
                        if (debug):
                            print ("Não foi possível desalocar o projeto. Consome mais que a janela")
                        return s, False, node_janela, gastos, sondas, f, max_free, total_free, total_setup
                    # senão, se consome a janela inteira
                    elif ((node.data[1] - (node.next.data[2] - delta_setup)) == 1):
                        if (debug):
                            print ("Sucesso ao desalocar projeto. Janela consumida integralmente.")
                        s[sonda].remove_node_by_ref(node.next)
                        node.next.next.data[1] -= (delta_setup)
                    # senão, se consome menos que a janela
                    else:
                        if (debug):
                            print ("Sucesso ao desalocar projeto. Janela consumida parcialmente.")
                        node.next.data[1] = node.data[1]
                        node.next.data[2] -= (delta_setup)
                        node.next.next.data[1] -= (delta_setup)
                        node_janela = node.next
                
                s[sonda].remove_node_by_ref(node)
            
            # e tem projeto depois
            elif (node.next.data[0] != -1):
                
                if (debug):
                    print ("Projeto está no primeiro node e tem projeto em seguida")
                
                # verificar se modifica setup 
                s, delta_setup, setup = VerificarSetupRemovendoNodeProjeto(s, sonda, node, desloc)
                
                proc = dados[21][projeto]
                
                # criar janela
                
                if (delta_setup == 0):
                    if (debug):
                        print ("delta setup = 0")
                    node.data[0] = -1
                    node_janela = node
                elif (delta_setup < 0):
                    if (debug):
                        print ("delta setup < 0 : libera espaço")
                    node.data[0] = -1
                    node.data[2] += -(delta_setup)
                    node.next.data[1] += -(delta_setup)
                    node_janela = node
                elif (delta_setup > 0):
                    
                    if (debug):
                        print ("delta setup > 0: consome espaço")
                    
                    if (node.next.data[1] - delta_setup < dados[22][node.next.data[0]]):
                        if (debug):
                            print ("Não foi possível desalocar o projeto. Janela inviável.")
                        return s, False, node_janela, gastos, sondas, f, max_free, total_free, total_setup
                    
                    # se delta setup consome mais do que a janela
                    if ((node.data[1] - (node.data[2] - delta_setup)) > 1):
                        if (debug):
                            print ("Não foi possível desalocar o projeto. Consome mais que a janela.")
                        return s, False, node_janela, gastos, sondas, f, max_free, total_free, total_setup
                    # senão, se consome a janela inteira
                    elif ((node.data[1] - (node.data[2] - delta_setup)) == 1):
                        if (debug):
                            print ("Sucesso ao desalocar projeto. Janela consumida integralmente.")
                        s[sonda].remove_node_by_ref(node)
                        node.next.data[1] -= (delta_setup)
                    # senão, se consome menos que a janela
                    else:
                        if (debug):
                            print ("Sucesso ao desalocar projeto. Janela consumida parcialmente.")
                        node.data[0] = -1
                        node.data[2] -= (delta_setup)
                        node.next.data[1] -= (delta_setup)
                        node_janela = node
        
        # senão, se for último node
        elif (node.next == None):
            
            # verificar se modifica setup 
            s, delta_setup, setup = VerificarSetupRemovendoNodeProjeto(s, sonda, node, desloc)
            
            proc = dados[21][projeto]
            
            # e tem janela antes
            if (node.prev.data[0] == -1):
                
                if (debug):
                    print ("Projeto está no último node e tem janela antes")
                
                # unir com janela
                node.prev.data[2] = node.data[2]
                node_janela = node.prev
                s[sonda].remove_node_by_ref(node)
            
            # e tem projeto antes
            elif (node.prev.data[0] != -1):
                
                if (debug):
                    print ("Projeto está no último node e tem projeto antes")
                
                # criar janela
                node.data[0] = -1
                node_janela = node
        
        # senão, se tem nodes antes e depois
        else:
            
            # se node antes é janela e node depois é janela
            if ( (node.prev.data[0] == -1) and (node.next.data[0] == -1) ):
                
                if (debug):
                    print ("Projeto está entre node de janela (antes) e node de janela (depois)")
                
                # verificar se modifica setup 
                s, delta_setup, setup = VerificarSetupRemovendoNodeProjeto(s, sonda, node, desloc)
                
                proc = dados[21][projeto]
                
                # unir 3 janelas
                
                if (delta_setup == 0):
                    if (debug):
                        print ("delta setup = 0")
                    node.prev.data[2] = node.next.data[2]
                    node_janela = node.prev
                elif (delta_setup < 0):
                    if (debug):
                        print ("delta setup < 0 : libera espaço")
                    node.prev.data[2] = node.next.data[2]
                    node.prev.data[2] += -(delta_setup)
                    node.next.next.data[1] += -(delta_setup)
                    node_janela = node.prev
                elif (delta_setup > 0):
                    
                    if (debug):
                        print ("delta setup > 0 : consome espaço")
                    
                    if (node.next.next.data[1] - delta_setup < dados[22][node.next.next.data[0]]):
                        if (debug):
                            print ("Não foi possível desalocar o projeto. Janela inviável.")
                        return s, False, node_janela, gastos, sondas, f, max_free, total_free, total_setup
                    
                    # se delta setup consome mais do que a janela
                    if ((node.prev.data[1] - (node.next.data[2] - delta_setup)) > 1):
                        if (debug):
                            print ("Não foi possível desalocar o projeto. Consome mais que a janela.")
                        return s, False, node_janela, gastos, sondas, f, max_free, total_free, total_setup
                    # senão, se consome a janela inteira
                    elif ((node.prev.data[1] - (node.next.data[2] - delta_setup)) == 1):
                        if (debug):
                            print ("Sucesso ao desalocar projeto. Janela consumida integralmente.")
                        s[sonda].remove_node_by_ref(node.prev)
                        node.next.next.data[1] -= (delta_setup)
                    # senão, se consome menos que a janela
                    else:
                        if (debug):
                            print ("Sucesso ao desalocar projeto. Janela consumida parcialmente.")
                        node.prev.data[2] = node.next.data[2]
                        node.prev.data[2] -= (delta_setup)
                        node.next.next.data[1] -= (delta_setup)
                        node_janela = node.prev
                
                s[sonda].remove_node_by_ref(node.next)
                s[sonda].remove_node_by_ref(node)
            
            # se node antes é projeto e node depois é janela
            elif ( (node.prev.data[0] != -1) and (node.next.data[0] == -1) ):
                
                if (debug):
                    print ("Projeto está entre node de projeto (antes) e node de janela (depois)")
                
                # verificar se modifica setup 
                s, delta_setup, setup = VerificarSetupRemovendoNodeProjeto(s, sonda, node, desloc)
                
                proc = dados[21][projeto]
                
                # unir com janela posterior
                
                if (delta_setup == 0):
                    if (debug):
                        print ("delta setup = 0")
                    node.next.data[1] = node.data[1]
                    node_janela = node.next
                elif (delta_setup < 0):
                    if (debug):
                        print ("delta setup < 0 : libera espaço")
                    node.next.data[1] = node.data[1]
                    node.next.data[2] += -(delta_setup)
                    node.next.next.data[1] += -(delta_setup)
                    node_janela = node.next
                elif (delta_setup > 0):
                    
                    if (debug):
                        print ("delta setup > 0 : consome espaço")
                    
                    if (node.next.next.data[1] - delta_setup < dados[22][node.next.next.data[0]]):
                        if (debug):
                            print ("Não foi possível desalocar o projeto. Janela inviável.")
                        return s, False, node_janela, gastos, sondas, f, max_free, total_free, total_setup
                    
                    # se delta setup consome mais do que a janela
                    if ((node.data[1] - (node.next.data[2] - delta_setup)) > 1):
                        if (debug):
                            print ("Não foi possível desalocar o projeto. Consome mais que a janela.")
                        return s, False, node_janela, gastos, sondas, f, max_free, total_free, total_setup
                    # senão, se consome a janela inteira
                    elif ((node.data[1] - (node.next.data[2] - delta_setup)) == 1):
                        if (debug):
                            print ("Sucesso ao desalocar projeto. Janela consumida integralmente.")
                        s[sonda].remove_node_by_ref(node.next)
                        node.next.next.data[1] -= (delta_setup)
                    # senão, se consome menos que a janela
                    else:
                        if (debug):
                            print ("Sucesso ao desalocar projeto. Janela consumida parcialmente.")
                        node.next.data[1] = node.data[1]
                        node.next.data[2] -= (delta_setup)
                        node.next.next.data[1] -= (delta_setup)
                        node_janela = node.next
                
                s[sonda].remove_node_by_ref(node)
            
            # se node antes é janela e node depois é projeto
            elif ( (node.prev.data[0] == -1) and (node.next.data[0] != -1) ):
                
                if (debug):
                    print ("Projeto está entre node de janela (antes) e node de projeto (depois)")
                
                # verificar se modifica setup
                s, delta_setup, setup = VerificarSetupRemovendoNodeProjeto(s, sonda, node, desloc)
                
                proc = dados[21][projeto]
                
                # unir com janela anterior
                
                if (delta_setup == 0):
                    if (debug):
                        print ("delta setup = 0")
                    node.prev.data[2] = node.data[2]
                    node_janela = node.prev
                elif (delta_setup < 0):
                    if (debug):
                        print ("delta setup < 0 : libera espaço")
                    node.prev.data[2] = node.data[2]
                    node.prev.data[2] += -(delta_setup)
                    node.next.data[1] += -(delta_setup)
                    node_janela = node.prev
                elif (delta_setup > 0):
                    
                    if (debug):
                        print ("delta setup > 0 : consome espaço")
                    
                    if (node.next.data[1] - delta_setup < dados[22][node.next.data[0]]):
                        if (debug):
                            print ("Não foi possível desalocar o projeto. Janela inviável.")
                        return s, False, node_janela, gastos, sondas, f, max_free, total_free, total_setup
                    
                    # se delta setup consome mais do que a janela
                    if ((node.prev.data[1] - (node.data[2] - delta_setup)) > 1):
                        if (debug):
                            print ("Não foi possível desalocar o projeto. Consome mais que a janela.")
                        return s, False, node_janela, gastos, sondas, f, max_free, total_free, total_setup
                    # senão, se consome a janela inteira
                    elif ((node.prev.data[1] - (node.data[2] - delta_setup)) == 1):
                        if (debug):
                            print ("Sucesso ao desalocar projeto. Janela consumida integralmente.")
                        s[sonda].remove_node_by_ref(node.prev)
                        node.next.data[1] -= (delta_setup)
                    # senão, se consome menos que a janela
                    else:
                        if (debug):
                            print ("Sucesso ao desalocar projeto. Janela consumida parcialmente.")
                        node.prev.data[2] = node.data[2]
                        node.prev.data[2] -= (delta_setup)
                        node.next.data[1] -= (delta_setup)
                        node_janela = node.prev
                
                s[sonda].remove_node_by_ref(node)
            
            # se node antes é projeto e node depois é projeto
            elif ( (node.prev.data[0] != -1) and (node.next.data[0] != -1) ):
                
                if (debug):
                    print ("Projeto está entre node de projeto (antes) e node de projeto (depois)")
                
                # verificar se modifica setup
                s, delta_setup, setup = VerificarSetupRemovendoNodeProjeto(s, sonda, node, desloc)
                
                proc = dados[21][projeto]
                
                # criar janela
                
                if (delta_setup == 0):
                    if (debug):
                        print ("delta setup = 0")
                    node.data[0] = -1
                    node_janela = node
                elif (delta_setup < 0):
                    if (debug):
                        print ("delta setup < 0 : libera espaço")
                    node.data[0] = -1
                    node.data[2] += -(delta_setup)
                    node.next.data[1] += -(delta_setup)
                    node_janela = node
                elif (delta_setup > 0):
                    
                    if (debug):
                        print ("delta setup > 0 : consome espaço")
                    
                    if (node.next.data[1] - delta_setup < dados[22][node.next.data[0]]):
                        if (debug):
                            print ("Não foi possível desalocar o projeto. Janela inviável.")
                        return s, False, node_janela, gastos, sondas, f, max_free, total_free, total_setup
                    
                    # se delta setup consome mais do que a janela
                    if ((node.data[1] - (node.data[2] - delta_setup)) > 1):
                        if (debug):
                            print ("Não foi possível desalocar o projeto. Consome mais que a janela.")
                        return s, False, node_janela, gastos, sondas, f, max_free, total_free, total_setup
                    # senão, se consome a janela inteira
                    elif ((node.data[1] - (node.data[2] - delta_setup)) == 1):
                        if (debug):
                            print ("Sucesso ao desalocar projeto. Janela consumida integralmente.")
                        s[sonda].remove_node_by_ref(node)
                        node.next.data[1] -= (delta_setup)
                    # senão, se consome menos que a janela
                    else:
                        if (debug):
                            print ("Sucesso ao desalocar projeto. Janela consumida parcialmente.")
                        node.data[0] = -1
                        node.data[2] -= (delta_setup)
                        node.next.data[1] -= (delta_setup)
                        node_janela = node
    
    
    # atualizar dados
    gastos -= dados[20][projeto]
    if (debug):
        print ("Sondas:", sondas)
    tam_prev = [v for (v,k) in sondas if (k==sonda)][0]
    sondas.remove((tam_prev, sonda))
    heapq.heappush(sondas, ( (tam_prev - (setup + proc - delta_setup)) , sonda))
    heapq.heapify(sondas)
    f -= dados[19][projeto]
    total_free += (setup + proc - delta_setup)
    total_setup -= (setup - delta_setup)
    max_free = copy.deepcopy(sondas[0][0])
    
    if (debug):
        print ("Sucesso ao desalocar projeto e atualizar dados")
        check = VerificaRestricoes(s, dados, f, gastos, desloc, sondas, max_free, total_free, total_setup, debug)
        if (check):
            check_str = "viável"
        else:
            check_str = "inviável"
        print ("Nova solução ", check_str)
        PrintSolution(s)
    
    return s, True, node_janela, gastos, sondas, f, max_free, total_free, total_setup


def DesalocarProjeto(s, projeto, desloc, dados, gastos, sondas, f, max_free, total_free, total_setup, debug=False):
    
    import CPUtimer
    
    timer = CPUtimer.CPUTimer()
    timer.reset()
    timer.start()
    
    for sonda in range(len(s.keys())):
        
        for node in s[sonda]:
            
            if (node.data[0] == projeto):
                
                s, flag, node_janela, gastos, sondas, f, max_free, total_free, total_setup = DesalocarProjetoPorNode(s, projeto, node, sonda, desloc, dados, gastos, sondas,
                            f, max_free, total_free, total_setup, debug)
    
    tempo_total = timer.get_time(reference = "total", unit = "seconds")
    
    if (debug):
        print ("Tempo gasto removendo projeto: ", tempo_total)
    
    return s, flag, node_janela, gastos, sondas, f, max_free, total_free, total_setup


def Remover_Projetos(s, k, desloc, dados, gastos, sondas, f, max_free, total_free, total_setup, debug=False):
    
    import copy
    import numpy as np
    
    # inicializa conjunto de projetos já selecionados
    proj_usados = set()
    for sonda in range(len(s.keys())):
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_usados.add(node.data[0])
    
    if (debug):
        print ("Removendo ", k, " projetos da solução...")
    
    i = 0
    while (i < k) and (k <= len(proj_usados)):
        
        # escolher um projeto
        projeto = np.random.choice(list(proj_usados))
        proj_usados.remove(projeto)
        
        # remover projeto
        s, removed_flag, node_janela, gastos, sondas, f, max_free, total_free, total_setup = DesalocarProjeto(s, projeto, desloc, dados, gastos, sondas, f, max_free, total_free, total_setup, debug)
        
        if (removed_flag):
            i += 1
    
    return s, gastos, sondas, f, max_free, total_free, total_setup

def Iterated_Greedy(arquivo, n_iter=100, criterios=None, alpha=0.5, print_sol=True, debug=False):
    
    """
    Documentação:
    """
    
    import CPUtimer
    import copy
    import numpy as np
    
    print ("Rodando Iterated Greedy...")
    
    if criterios == None:
        criterios = ['lucro', 'lucro/custo', 'lucro/duracao'] #, 'custo', 'duracao', 'janela']
    
    n_projetos, n_sondas, n_periodos, t_init, t_final, delta_t, custo_total, dados, desloc = Read_data(path=arquivo)
    
    criterio = np.random.choice(criterios)
    
    if (debug):
        print ("Construindo solução inicial...")
    
    f, gastos, s, s_candidatos, sondas, total_free, total_setup, max_free, _ = ConstruirSolucao(dados, n_projetos, n_sondas, 
                                                                         n_periodos, custo_total, desloc,
                                                                         criterio=criterio, alpha=alpha, debug=debug)
    
    if (debug):
        print ("Solução inicial construída.")
    
    best_f = copy.deepcopy(f)
    best_gastos = copy.deepcopy(gastos)
    best_s = copy.deepcopy(s) 
    best_total_free = copy.deepcopy(total_free)
    best_total_setup = copy.deepcopy(total_setup)
    best_max_free = copy.deepcopy(max_free)
    best_sondas = copy.deepcopy(sondas)
    
    timer = CPUtimer.CPUTimer()
    timer.reset()
    timer.start()
    
    i = 1
    while(n_iter >= i):
        
        #print ("Iteração: ", i)
        
        i += 1
        
        proj_count = 0
        for sonda in range(len(s.keys())):
            for node in s[sonda]:
                if (node.data[0] != -1):
                    proj_count += 1
        
        if ( (proj_count // 2) > 1 ):
            k = np.random.choice(range(1, proj_count // 2))
        else:
            k = 1
        
        # remover k projetos aleatoriamente
        s, gastos, sondas, f, max_free, total_free, total_setup = Remover_Projetos(s, k, desloc, dados, gastos, sondas, f, max_free, total_free, total_setup, debug)
        
        criterio = np.random.choice(criterios)
        
        alpha = np.random.choice([0.7, 0.8, 0.85, 0.9, 0.95, 0.99])
        
        if (debug):
            print ("Reconstruindo solução...")
        # reconstruir solução
        f_temp, gastos_temp, s_temp, _, sondas_temp, total_free_temp, total_setup_temp, max_free_temp, _ = ConstruirSolucao(dados, n_projetos,
                                                                                             n_sondas, 
                                                                                             n_periodos, 
                                                                                             custo_total, 
                                                                                             desloc,
                                                                                             criterio=criterio, alpha=alpha, s=s,
                                                                                                                        debug=debug)
        if (debug):
            print ("Solução reconstruída.")
        
        if (f_temp > 0.7*f):
            f = copy.deepcopy(f_temp)
            gastos = copy.deepcopy(gastos_temp)
            s = copy.deepcopy(s_temp)
            total_free = copy.deepcopy(total_free_temp)
            total_setup = copy.deepcopy(total_setup_temp)
            max_free = copy.deepcopy(max_free_temp)
            sondas = copy.deepcopy(sondas_temp)
        
        if (f > best_f):
            best_f = copy.deepcopy(f)
            best_gastos = copy.deepcopy(gastos)
            best_s = copy.deepcopy(s)
            best_total_free = copy.deepcopy(total_free)
            best_total_setup = copy.deepcopy(total_setup)
            best_max_free = copy.deepcopy(max_free)
            best_sondas = copy.deepcopy(sondas)
    
    check = VerificaRestricoes(best_s, dados, best_f, best_gastos, desloc, best_sondas, 
                               best_max_free, best_total_free, best_total_setup, debug)
    
    tempo_total = timer.get_time(reference = "total", unit = "seconds")
    tempo_medio = timer.get_time(reference = "average", unit = "seconds")
    
    if check:
        check_str = 'feasible'
    else:
        check_str = 'not feasible'
    
    if print_sol:
        print (check_str)
        print ('fitness: ', best_f)
        print ('gastos: ', best_gastos)
        print ('tempo total de execução (segundos) : ', tempo_total)
        print ('tempo médio de execução (segundos) ', tempo_medio)
        for i in range(n_sondas):
            for node in best_s[i]:
                print ('sonda ', i, ' executa projetos: ', node.data)
    
    print ("Iterated Greedy concluído.")
    
    return best_f, best_gastos, best_s, tempo_total, tempo_medio, check_str

def PreProcessamento(s, desloc, dados, lag, proj_nao_usados, k=5, debug=False):
    
    """
    Documentação:
    
     cada dicionário guarda como key o projeto analisado para a operação a ser feita...
     e como valores uma lista de (sonda, projeto) ou (sonda, janela) sendo as melhores opções p/ a operação
     
     key = projeto
     key = (projeto1, projeto2)
     
     val = (projeto, sonda, criterio)
     val = (-1, sonda, release, due)
     
    """
    
    import CPUtimer
    
    if (debug):
        print ("Rodando pré-processamento...")
        print ("Solução inicial:")
        PrintSolution(s)
    
    timer = CPUtimer.CPUTimer()
    timer.reset()
    timer.start()
    
    shift_dict = {}
    for sonda1 in s.keys():
        for node1 in s[sonda1]:
            if (node1.data[0] != -1):
                projeto1 = node1.data[0]
                shift_dict[projeto1] = []
                proj_set = set()
                for sonda2 in s.keys():
                    if (sonda1 == sonda2):
                        continue
                    for node2 in s[sonda2]:
                        if (node2.data[0] != -1):
                            projeto2 = node2.data[0]
                            dist = desloc[projeto1 + lag][projeto2 + lag]
                            if (len(shift_dict[projeto1]) < k):
                                shift_dict[projeto1].append((projeto2, sonda2, dist))
                                shift_dict[projeto1] = sorted(shift_dict[projeto1], key=lambda x: x[2], reverse=False)
                                proj_set.add(projeto2)
                            else:
                                if (dist < shift_dict[projeto1][-1][2]):
                                    projeto_del = shift_dict[projeto1][-1][0]
                                    del shift_dict[projeto1][-1]
                                    shift_dict[projeto1].append((projeto2, sonda2, dist))
                                    shift_dict[projeto1] = sorted(shift_dict[projeto1], key=lambda x: x[2], reverse=False)
                                    proj_set.remove(projeto_del)
                                    proj_set.add(projeto2)
                for sonda2 in s.keys():
                    if (sonda1 == sonda2):
                        continue
                    for node2 in s[sonda2]:
                        if (node2.data[0] == -1):
                            if (node2.next != None):
                                if (node2.next.data[0] in proj_set):
                                    release = node2.data[1]
                                    due = node2.data[2]
                                    if ((-1, sonda2, release, due) not in shift_dict[projeto1]):
                                        shift_dict[projeto1].append((-1, sonda2, release, due))
                            if (node2.prev != None):
                                if (node2.prev.data[0] in proj_set):
                                    release = node2.data[1]
                                    due = node2.data[2]
                                    if ((-1, sonda2, release, due) not in shift_dict[projeto1]):
                                        shift_dict[projeto1].append((-1, sonda2, release, due))
    
    remove_dict = {}
    for sonda1 in s.keys():
        for node1 in s[sonda1]:
            if (node1.data[0] != -1):
                projeto1 = node1.data[0]
                remove_dict[projeto1] = []
                for node2 in s[sonda1]:
                    if (node2.data[0] != -1):
                        if (node2.data[0] == projeto1):
                            continue
                        projeto2 = node2.data[0]
                        dist = desloc[projeto1 + lag][projeto2 + lag]
                        if (len(remove_dict[projeto1]) < k):
                            remove_dict[projeto1].append((projeto2, sonda1, dist))
                            remove_dict[projeto1] = sorted(remove_dict[projeto1], key=lambda x: x[2], reverse=False)
                        else:
                            if (dist < remove_dict[projeto1][-1][2]):
                                del remove_dict[projeto1][-1]
                                remove_dict[projeto1].append((projeto2, sonda1, dist))
                                remove_dict[projeto1] = sorted(remove_dict[projeto1], key=lambda x: x[1], reverse=False)
    
    swap_dict = {}
    for sonda1 in s.keys():
        for node1 in s[sonda1]:
            if (node1.data[0] != -1):
                projeto1 = node1.data[0]
                swap_dict[projeto1] = []
                for sonda2 in s.keys():
                    if (sonda1 == sonda2):
                        continue
                    for node2 in s[sonda2]:
                        if (node2.data[0] != -1):
                            projeto2 = node2.data[0]
                            dist = desloc[projeto1 + lag][projeto2 + lag]
                            if (len(swap_dict[projeto1]) < k):
                                swap_dict[projeto1].append((projeto2, sonda2, dist))
                                swap_dict[projeto1] = sorted(swap_dict[projeto1], key=lambda x: x[2], reverse=False)
                            else:
                                if (dist < swap_dict[projeto1][-1][2]):
                                    del swap_dict[projeto1][-1]
                                    swap_dict[projeto1].append((projeto2, sonda2, dist))
                                    swap_dict[projeto1] = sorted(swap_dict[projeto1], key=lambda x: x[2], reverse=False)
    
    reinsert_dict = {}
    for sonda1 in s.keys():
        for node1 in s[sonda1]:
            if (node1.data[0] != -1):
                projeto1 = node1.data[0]
                reinsert_dict[projeto1] = []
                proj_set = set()
                for node2 in s[sonda1]:
                    if (node2.data[0] != -1):
                        if (node2.data[0] == projeto1):
                            continue
                        projeto2 = node2.data[0]
                        dist = desloc[projeto1 + lag][projeto2 + lag]
                        if (len(reinsert_dict[projeto1]) < k):
                            reinsert_dict[projeto1].append((projeto2, sonda1, dist))
                            reinsert_dict[projeto1] = sorted(reinsert_dict[projeto1], key=lambda x: x[2], reverse=False)
                            proj_set.add(projeto2)
                        else:
                            if (dist < reinsert_dict[projeto1][-1][2]):
                                projeto_del = reinsert_dict[projeto1][-1][0]
                                del reinsert_dict[projeto1][-1]
                                reinsert_dict[projeto1].append((projeto2, sonda1, dist))
                                reinsert_dict[projeto1] = sorted(reinsert_dict[projeto1], key=lambda x: x[2], reverse=False)
                                proj_set.remove(projeto_del)
                                proj_set.add(projeto2)
                proj_set.add(projeto1)
                for node2 in s[sonda1]:
                    if (node2.data[0] == -1):
                        if (node2.next != None):
                            if (node2.next.data[0] in proj_set):
                                release = node2.data[1]
                                due = node2.data[2]
                                if ((-1, sonda1, release, due) not in reinsert_dict[projeto1]):
                                    reinsert_dict[projeto1].append((-1, sonda1, release, due))
                        if (node2.prev != None):
                            if (node2.prev.data[0] in proj_set):
                                release = node2.data[1]
                                due = node2.data[2]
                                if ((-1, sonda1, release, due) not in reinsert_dict[projeto1]):
                                    reinsert_dict[projeto1].append((-1, sonda1, release, due))
    
    insert_fo_dict = {}
    for projeto1 in proj_nao_usados:
        insert_fo_dict[projeto1] = []
        proj_set = set()
        for sonda in s.keys():
            for node in s[sonda]:
                if (node.data[0] != -1):
                    projeto2 = node.data[0]
                    dist = desloc[projeto1 + lag][projeto2 + lag]
                    if (len(insert_fo_dict[projeto1]) < k):
                        insert_fo_dict[projeto1].append((projeto2, sonda, dist))
                        insert_fo_dict[projeto1] = sorted(insert_fo_dict[projeto1], key=lambda x: x[2], reverse=False)
                        proj_set.add(projeto2)
                    else:
                        if (dist < insert_fo_dict[projeto1][-1][2]):
                            projeto_del = insert_fo_dict[projeto1][-1][0]
                            del insert_fo_dict[projeto1][-1]
                            insert_fo_dict[projeto1].append((projeto2, sonda, dist))
                            insert_fo_dict[projeto1] = sorted(insert_fo_dict[projeto1], key=lambda x: x[2], reverse=False)
                            proj_set.remove(projeto_del)
                            proj_set.add(projeto2)
        for sonda in s.keys():
            for node in s[sonda]:
                if (node.data[0] == -1):
                    if (node.next != None):
                        if (node.next.data[0] in proj_set):
                            release = node.data[1]
                            due = node.data[2]
                            if ((-1, sonda, release, due) not in insert_fo_dict[projeto1]):
                                insert_fo_dict[projeto1].append((-1, sonda, release, due))
                    if (node.prev != None):
                        if (node.prev.data[0] in proj_set):
                            release = node.data[1]
                            due = node.data[2]
                            if ((-1, sonda, release, due) not in insert_fo_dict[projeto1]):
                                insert_fo_dict[projeto1].append((-1, sonda2, release, due))
    
    swap_1x1_fo_dict = {}
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                projeto1 = node.data[0]
                custo1 = dados[20][projeto1]
                swap_1x1_fo_dict[projeto1] = []
                for proj2 in proj_nao_usados:
                    # que projetos vou dar preferência para substituir o projeto1?
                    # projetos com alto valor/custo, mas que não tenham maior custo que projeto1?
                    # projetos próximos ao projeto1, mas que não tenham maior custo que projeto1?
                    # projetos com alto valor/dist, mas que não tenham maior custo que projeto1!
                    projeto2 = proj2
                    dist = desloc[projeto1 + lag][projeto2 + lag]
                    valor = dados[19][projeto2]
                    criterio = round((valor)/(dist+0.01), 2)
                    custo2 = dados[20][projeto2]
                    if (custo2 > custo1*1.2): # fator multiplicativo ajustável
                        continue
                    if (len(swap_1x1_fo_dict[projeto1]) < k):
                        swap_1x1_fo_dict[projeto1].append((projeto2, sonda, criterio))
                        swap_1x1_fo_dict[projeto1] = sorted(swap_1x1_fo_dict[projeto1], key=lambda x: x[2], reverse=True)
                    else:
                        if (criterio > swap_1x1_fo_dict[projeto1][-1][2]):
                            del swap_1x1_fo_dict[projeto1][-1]
                            swap_1x1_fo_dict[projeto1].append((projeto2, sonda, criterio))
                            swap_1x1_fo_dict[projeto1] = sorted(swap_1x1_fo_dict[projeto1], key=lambda x: x[2], reverse=True)
    
    swap_1x2_fo_dict = {}
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                projeto1 = node.data[0]
                custo1 = dados[20][projeto1]
                swap_1x2_fo_dict[projeto1] = []
                for proj2 in proj_nao_usados:
                    # que projetos vou dar preferência para substituir o projeto1?
                    # projetos com alto valor/custo, mas que não tenham maior custo que projeto1?
                    # projetos próximos ao projeto1, mas que não tenham maior custo que projeto1?
                    # projetos com alto valor/dist, mas que não tenham maior custo que projeto1!
                    projeto2 = proj2
                    dist = desloc[projeto1 + lag][projeto2 + lag]
                    valor = dados[19][projeto2]
                    criterio = round((valor)/(dist+0.01), 2)
                    custo2 = dados[20][projeto2]
                    if (custo2 > custo1*0.8): # fator multiplicativo ajustável
                        continue
                    if (len(swap_1x2_fo_dict[projeto1]) < k):
                        swap_1x2_fo_dict[projeto1].append((projeto2, sonda, criterio))
                        swap_1x2_fo_dict[projeto1] = sorted(swap_1x2_fo_dict[projeto1], key=lambda x: x[2], reverse=True)
                    else:
                        if (criterio > swap_1x2_fo_dict[projeto1][-1][2]):
                            del swap_1x2_fo_dict[projeto1][-1]
                            swap_1x2_fo_dict[projeto1].append((projeto2, sonda, criterio))
                            swap_1x2_fo_dict[projeto1] = sorted(swap_1x2_fo_dict[projeto1], key=lambda x: x[2], reverse=True)
    
    swap_2x1_fo_dict = {}
    for sonda in s.keys():
        for node1 in s[sonda]:
            if (node1.data[0] != -1):
                projeto1 = node1.data[0]
                custo1 = dados[20][projeto1]
                for el in remove_dict[projeto1]:
                    projeto2, _, _ = el
                    custo2 = dados[20][projeto2]
                    swap_2x1_fo_dict[(projeto1, projeto2)] = []
                    for proj3 in proj_nao_usados:
                        # que projetos vou dar preferência para substituir o projeto1 e projeto2?
                        # projetos com alto valor/custo, mas que não tenham maior custo que projeto1 + projeto2?
                        # projetos próximos ao projeto1, mas que não tenham maior custo que projeto1 + projeto2?
                        # projetos com alto valor/dist, mas que não tenham maior custo que projeto1 + projeto2!
                        projeto3 = proj3
                        dist1 = desloc[projeto1 + lag][projeto3 + lag]
                        dist2 = desloc[projeto2 + lag][projeto3 + lag]
                        valor = dados[19][projeto3]
                        criterio = round((valor)/(((dist1 + dist2)/2)+0.01), 2)
                        custo3 = dados[20][projeto3]
                        if (custo3 > (custo1 + custo2)*1.2): # fator multiplicativo ajustável
                            continue
                        if (len(swap_2x1_fo_dict[(projeto1, projeto2)]) < k):
                            swap_2x1_fo_dict[(projeto1, projeto2)].append((projeto3, sonda, criterio))
                            swap_2x1_fo_dict[(projeto1, projeto2)] = sorted(swap_2x1_fo_dict[(projeto1, projeto2)], key=lambda x: x[2], reverse=True)
                        else:
                            if (criterio > swap_2x1_fo_dict[(projeto1, projeto2)][-1][2]):
                                del swap_2x1_fo_dict[(projeto1, projeto2)][-1]
                                swap_2x1_fo_dict[(projeto1, projeto2)].append((projeto3, sonda, criterio))
                                swap_2x1_fo_dict[(projeto1, projeto2)] = sorted(swap_2x1_fo_dict[(projeto1, projeto2)], key=lambda x: x[2], reverse=True)
    
    swap_2x2_fo_dict = {}
    for sonda in s.keys():
        for node1 in s[sonda]:
            if (node1.data[0] != -1):
                projeto1 = node1.data[0]
                custo1 = dados[20][projeto1]
                for el in remove_dict[projeto1]:
                    projeto2, _, _ = el
                    custo2 = dados[20][projeto2]
                    swap_2x2_fo_dict[(projeto1, projeto2)] = []
                    for proj3 in proj_nao_usados:
                        # que projetos vou dar preferência para substituir o projeto1 e projeto2?
                        # projetos com alto valor/custo, mas que não tenham maior custo que projeto1 + projeto2?
                        # projetos próximos ao projeto1, mas que não tenham maior custo que projeto1 + projeto2?
                        # projetos com alto valor/dist, mas que não tenham maior custo que projeto1 + projeto2!
                        projeto3 = proj3
                        dist1 = desloc[projeto1 + lag][projeto3 + lag]
                        dist2 = desloc[projeto2 + lag][projeto3 + lag]
                        valor = dados[19][projeto3]
                        criterio = round((valor)/(((dist1 + dist2)/2)+0.01), 2)
                        custo3 = dados[20][projeto3]
                        if (custo3 > (custo1 + custo2)*0.8): # fator multiplicativo ajustável
                            continue
                        if (len(swap_2x2_fo_dict[(projeto1, projeto2)]) < k):
                            swap_2x2_fo_dict[(projeto1, projeto2)].append((projeto3, sonda, criterio))
                            swap_2x2_fo_dict[(projeto1, projeto2)] = sorted(swap_2x2_fo_dict[(projeto1, projeto2)], key=lambda x: x[2], reverse=True)
                        else:
                            if (criterio > swap_2x2_fo_dict[(projeto1, projeto2)][-1][2]):
                                del swap_2x2_fo_dict[(projeto1, projeto2)][-1]
                                swap_2x2_fo_dict[(projeto1, projeto2)].append((projeto3, sonda, criterio))
                                swap_2x2_fo_dict[(projeto1, projeto2)] = sorted(swap_2x2_fo_dict[(projeto1, projeto2)], key=lambda x: x[2], reverse=True)
    
    tempo_total = timer.get_time(reference = "total", unit = "seconds")
    
    if (debug):
        print ("Pré-processamento finalizado.")
        print ("")
        print ("shift_dict =", shift_dict)
        print ("")
        print ("remove_dict =", remove_dict)
        print ("")
        print ("swap_dict =", swap_dict)
        print ("")
        print ("reinsert_dict =", reinsert_dict)
        print ("")
        print ("insert_fo_dict =", insert_fo_dict)
        print ("")
        print ("swap_1x1_fo_dict =", swap_1x1_fo_dict)
        print ("")
        print ("swap_1x2_fo_dict =", swap_1x2_fo_dict)
        print ("")
        print ("swap_2x1_fo_dict =", swap_2x1_fo_dict)
        print ("")
        print ("swap_2x2_fo_dict =", swap_2x2_fo_dict)
        print ("")
        print ("Tempo gasto com pré-processamento: ", tempo_total)
    
    return shift_dict, remove_dict, swap_dict, reinsert_dict, insert_fo_dict, swap_1x1_fo_dict, swap_1x2_fo_dict, swap_2x1_fo_dict, swap_2x2_fo_dict, tempo_total

def shift_1x0_interrota(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, debug=False, k=5):
    
    """
    Documentação: 
    
    Remove projeto de uma sonda e tenta colocar em outra sonda.
    
    """
    
    if (debug):
        print ("Rodando estrutura de vizinhança: shift(1, 0)")
        print ("Solução inicial tem:")
        print ("f =", f)
        print ("gastos =", gastos)
        print ("total_free =", total_free)
        print ("max_free =", max_free)
        print ("total_setup =", total_setup)
        print ("sondas:", sondas)
    
    import pickle
    import copy
    import heapq
    import CPUtimer
    from time import process_time
    
    s_best = copy.deepcopy(s)
    gastos_best = copy.copy(gastos)
    sondas_best = copy.deepcopy(sondas)
    f_best = copy.copy(f)
    max_free_best = copy.copy(max_free)
    total_free_best = copy.copy(total_free)
    total_setup_best = copy.copy(total_setup)
    
    # gera conjunto de projetos já alocados
    proj_usados = set()
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_usados.add(node.data[0])
    
    # gera conjunto de projetos não alocados
    proj_nao_usados = set()
    for j in range(len(dados[4])):
        if j not in proj_usados:
            if (dados[19][j] > 0):
                proj_nao_usados.add(j)
    
    ans = PreProcessamento(s, desloc, dados, lag, proj_nao_usados, k=k, debug=debug)
    shift_dict, remove_dict, swap_dict, reinsert_dict, insert_fo_dict, swap_1x1_fo_dict, swap_1x2_fo_dict, swap_2x1_fo_dict, swap_2x2_fo_dict, tempo_preproc = ans
    
    timer_geral = CPUtimer.CPUTimer()
    timer_geral.reset()
    timer_geral.start()
    
    timer_find = CPUtimer.CPUTimer()
    timer_find.reset()
    
    timer_insere = CPUtimer.CPUTimer()
    timer_insere.reset()
    
    timer_remove = CPUtimer.CPUTimer()
    timer_remove.reset()
    
    timer_copy = CPUtimer.CPUTimer()
    timer_copy.reset()
    
    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
    outfile = open(filename, 'wb')
    pickle.dump(s, outfile)
    outfile.close()
    
    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1_s.pkl'
    outfile = open(filename, 'wb')
    pickle.dump(sondas, outfile)
    outfile.close()
    
    # enumera todos os projetos que posso tentar remover
    for sonda1 in s.keys():
        for node1 in s[sonda1]:
            
            timer_copy.start()
            #s_removed = copy.deepcopy(s)
            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
            infile = open(filename, 'rb')
            s_removed = pickle.load(infile)
            infile.close()
            
            gastos_removed = copy.copy(gastos)
            
            #sondas_removed = copy.deepcopy(sondas)
            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1_s.pkl'
            infile = open(filename, 'rb')
            sondas_removed = pickle.load(infile)
            infile.close()
            
            f_removed = copy.copy(f)
            max_free_removed = copy.copy(max_free)
            total_free_removed = copy.copy(total_free)
            total_setup_removed = copy.copy(total_setup)
            timer_copy.stop()
            
            if (node1.data[0] != -1):
                
                timer_find.start()
                for node1_use in s_removed[sonda1]:
                    if (node1.data[0] == node1_use.data[0]):
                        break
                timer_find.stop()
                
                timer_remove.start()
                # tenta remover
                projeto = node1.data[0]
                proc = dados[21][projeto]
                s_removed, flag, node_janela, gastos_removed, sondas_removed, f_removed, max_free_removed, total_free_removed, total_setup_removed = DesalocarProjetoPorNode(s_removed, 
                                                                                projeto, node1_use, sonda1, desloc, 
                                                                                dados, gastos_removed, sondas_removed, f_removed, max_free_removed, 
                                                                                total_free_removed, total_setup_removed, debug)
                timer_remove.stop()
                
                # se não conseguir remover, vai para o próximo node
                if (flag == False):
                    continue
                
                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                outfile = open(filename, 'wb')
                pickle.dump(s_removed, outfile)
                outfile.close()
                
                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2_s.pkl'
                outfile = open(filename, 'wb')
                pickle.dump(sondas_removed, outfile)
                outfile.close()
                
                # tentar inserir em outra sonda: enumerar
                for el in shift_dict[projeto]:
                    
                    if (el[0] == -1):
                        _, sonda2, release, due = el
                        flag_el = "janela"
                    else:
                        projeto2, sonda2, _ = el
                        flag_el = "projeto"
                    
                    aloc = False
                    
                    timer_copy.start()
                    #s_local = copy.deepcopy(s_removed)
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                    infile = open(filename, 'rb')
                    s_local = pickle.load(infile)
                    infile.close()
                    
                    gastos_local = copy.copy(gastos_removed)
                    
                    #sondas_local = copy.deepcopy(sondas_removed)
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2_s.pkl'
                    infile = open(filename, 'rb')
                    sondas_local = pickle.load(infile)
                    infile.close()
                    
                    f_local = copy.copy(f_removed)
                    max_free_local = copy.copy(max_free_removed)
                    total_free_local = copy.copy(total_free_removed)
                    total_setup_local = copy.copy(total_setup_removed)
                    timer_copy.stop()
                    
                    tam_prev = [v for (v,k) in sondas_local if (k==sonda2)][0]
                    sondas_local.remove((tam_prev, sonda2))
                    heapq.heapify(sondas_local)
                    
                    timer_find.start()
                    if (flag_el == "janela"):
                        for node2_use in s_local[sonda2]:
                            if ((release == node2_use.data[1]) and (due == node2_use.data[2])):
                                break
                    elif (flag_el == "projeto"):
                        for node2_use in s_local[sonda2]:
                            if (projeto2 == node2_use.data[0]):
                                break
                    timer_find.stop()
                    
                    timer_insere.start()
                    if (flag_el == "janela"):
                        aloc, gastos_local, sondas_local, f_local, total_free_local, total_setup_local, max_free_local = TentaInserirNodeDeJanela(s_local, node2_use, sonda2, projeto, dados, lag, desloc, proc, aloc, gastos_local, sondas_local, f_local, max_free_local, total_free_local, total_setup_local, tam_prev, debug)
                    
                    elif (flag_el == "projeto"):
                        aloc, gastos_local, sondas_local, f_local, total_free_local, total_setup_local, max_free_local = TentaInserirNodeDeProjeto(s_local, node2_use, sonda2, projeto, dados, lag, desloc, proc, aloc, gastos_local, f_local, sondas_local, max_free_local, total_free_local, total_setup_local, tam_prev, debug)
                    timer_insere.stop()
                    
                    if (aloc):

                        if (total_free_local > total_free_best):

                            if (debug):
                                print ("Solução vizinha encontrada com melhor total_free")

                            s_best = copy.deepcopy(s_local)
                            gastos_best = copy.copy(gastos_local)
                            sondas_best = copy.deepcopy(sondas_local)
                            f_best = copy.copy(f_local)
                            max_free_best = copy.copy(max_free_local)
                            total_free_best = copy.copy(total_free_local)
                            total_setup_best = copy.copy(total_setup_local)

                        elif (total_free_local == total_free_best):

                            if (-max_free_local > -max_free_best):

                                if (debug):
                                    print ("Solução vizinha encontrada com melhor max_free")

                                s_best = copy.deepcopy(s_local)
                                gastos_best = copy.copy(gastos_local)
                                sondas_best = copy.deepcopy(sondas_local)
                                f_best = copy.copy(f_local)
                                max_free_best = copy.copy(max_free_local)
                                total_free_best = copy.copy(total_free_local)
                                total_setup_best = copy.copy(total_setup_local)

                            elif (-max_free_local == -max_free_best):

                                if (total_setup_local < total_setup_best):

                                    if (debug):
                                        print ("Solução vizinha encontrada com melhor total_setup")

                                    s_best = copy.deepcopy(s_local)
                                    gastos_best = copy.copy(gastos_local)
                                    sondas_best = copy.deepcopy(sondas_local)
                                    f_best = copy.copy(f_local)
                                    max_free_best = copy.copy(max_free_local)
                                    total_free_best = copy.copy(total_free_local)
                                    total_setup_best = copy.copy(total_setup_local)
    
    tempo_total = timer_geral.get_time(reference = "total", unit = "seconds")
    tempo_find = timer_find.get_time(reference = "total", unit = "seconds")
    tempo_insere = timer_insere.get_time(reference = "total", unit = "seconds")
    tempo_remove = timer_remove.get_time(reference = "total", unit = "seconds")
    tempo_copy = timer_copy.get_time(reference = "total", unit = "seconds")
    tempos = (tempo_preproc, tempo_total, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if (debug):
        print ("Solução final tem:")
        print ("f =", f_best)
        print ("gastos =", gastos_best)
        print ("total_free =", total_free_best)
        print ("max_free =", max_free_best)
        print ("total_setup =", total_setup_best)
        print ("sondas:", sondas)
        print ("Tempo gasto no shift_1x0_interrota: ", tempo_total)
    
    return s_best, gastos_best, sondas_best, f_best, max_free_best, total_free_best, total_setup_best, tempos

def shift_2x0_interrota(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, debug=False, k=5):
    
    """
    Documentação: 
    
    Remove 2 projetos de uma sonda e tenta colocar em outra sonda.
    
    """
    
    if (debug):
        print ("Rodando estrutura de vizinhança: shift(2, 0)")
        print ("Solução inicial tem:")
        print ("f =", f)
        print ("gastos =", gastos)
        print ("total_free =", total_free)
        print ("max_free =", max_free)
        print ("total_setup =", total_setup)
        print ("sondas:", sondas)
    
    import pickle
    import copy
    import heapq
    import CPUtimer
    from time import process_time
    
    s_best = copy.deepcopy(s)
    gastos_best = copy.copy(gastos)
    sondas_best = copy.deepcopy(sondas)
    f_best = copy.copy(f)
    max_free_best = copy.copy(max_free)
    total_free_best = copy.copy(total_free)
    total_setup_best = copy.copy(total_setup)
    
    # gera conjunto de projetos já alocados
    proj_usados = set()
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_usados.add(node.data[0])
    
    # gera conjunto de projetos não alocados
    proj_nao_usados = set()
    for j in range(len(dados[4])):
        if j not in proj_usados:
            if (dados[19][j] > 0):
                proj_nao_usados.add(j)
    
    ans = PreProcessamento(s, desloc, dados, lag, proj_nao_usados, k=k, debug=debug)
    shift_dict, remove_dict, swap_dict, reinsert_dict, insert_fo_dict, swap_1x1_fo_dict, swap_1x2_fo_dict, swap_2x1_fo_dict, swap_2x2_fo_dict, tempo_preproc = ans
    
    timer_geral = CPUtimer.CPUTimer()
    timer_geral.reset()
    timer_geral.start()
    
    timer_find = CPUtimer.CPUTimer()
    timer_find.reset()
    
    timer_insere = CPUtimer.CPUTimer()
    timer_insere.reset()
    
    timer_remove = CPUtimer.CPUTimer()
    timer_remove.reset()
    
    timer_copy = CPUtimer.CPUTimer()
    timer_copy.reset()
    
    # otimização 1
    pular1 = set()
    
    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
    outfile = open(filename, 'wb')
    pickle.dump(s, outfile)
    outfile.close()
    
    # enumera todos os projetos que posso tentar remover
    for sonda1 in s.keys():
        
        sonda1_use = copy.deepcopy(sonda1)
        
        for node1 in s[sonda1_use]:
            
            timer_copy.start()
            #s_removed1 = copy.deepcopy(s)
            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
            infile = open(filename, 'rb')
            s_removed1 = pickle.load(infile)
            infile.close()
            
            gastos_removed1 = copy.copy(gastos)
            sondas_removed1 = copy.deepcopy(sondas)
            f_removed1 = copy.copy(f)
            max_free_removed1 = copy.copy(max_free)
            total_free_removed1 = copy.copy(total_free)
            total_setup_removed1 = copy.copy(total_setup)
            timer_copy.stop()
            
            if (node1.data[0] != -1):
                
                timer_find.start()
                for node1_use in s_removed1[sonda1_use]:
                    if (node1.data[0] == node1_use.data[0]):
                        break
                timer_find.stop()
                
                # tenta remover
                projeto1 = node1_use.data[0]
                proc1 = dados[21][projeto1]
                
                if (debug):
                    print ("Tentando remover primeiro projeto: projeto:", projeto1)
                    print ("Projetos já removidos:", [])
                    check = VerificaRestricoes(s_removed1, dados, f_removed1, gastos_removed1, desloc, sondas_removed1, max_free_removed1, total_free_removed1, total_setup_removed1, debug)
                    if (check):
                        check_str = "viável"
                    else:
                        check_str = "inviável"
                    print ("Solução atual: ", check_str)
                    PrintSolution(s_removed1)
                
                timer_remove.start()
                s_removed1, flag1, node_janela, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, total_free_removed1, total_setup_removed1 = DesalocarProjetoPorNode(s_removed1, 
                                                                                projeto1, node1_use, sonda1_use, desloc, 
                                                                                dados, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, 
                                                                                total_free_removed1, total_setup_removed1, debug)
                timer_remove.stop()
                
                # se não conseguir remover, vai para o próximo node
                if (flag1 == False):
                    continue
                
                if (debug):
                    print ("Projeto ", projeto1, " removido.")
                    print ("Projetos já removidos:", [projeto1])
                    check = VerificaRestricoes(s_removed1, dados, f_removed1, gastos_removed1, desloc, sondas_removed1, max_free_removed1, total_free_removed1, total_setup_removed1, debug)
                    if (check):
                        check_str = "viável"
                    else:
                        check_str = "inviável"
                    print ("Nova solução ", check_str)
                    PrintSolution(s_removed1)
                
                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                outfile = open(filename, 'wb')
                pickle.dump(s_removed1, outfile)
                outfile.close()
                
                for el1 in remove_dict[projeto1]:
                    
                    projeto2, _, _ = el1
                    
                    timer_copy.start()
                    #s_removed2 = copy.deepcopy(s_removed1)
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                    infile = open(filename, 'rb')
                    s_removed2 = pickle.load(infile)
                    infile.close()
                    
                    gastos_removed2 = copy.copy(gastos_removed1)
                    sondas_removed2 = copy.deepcopy(sondas_removed1)
                    f_removed2 = copy.copy(f_removed1)
                    max_free_removed2 = copy.copy(max_free_removed1)
                    total_free_removed2 = copy.copy(total_free_removed1)
                    total_setup_removed2 = copy.copy(total_setup_removed1)
                    timer_copy.stop()
                    
                    timer_find.start()
                    for node3_use in s_removed2[sonda1_use]:
                        if (projeto2 == node3_use.data[0]):
                            break
                    timer_find.stop()
                    
                    # tenta remover
                    proc2 = dados[21][projeto2]
                    
                    # otimização 1
                    if ( tuple(sorted((projeto1, projeto2))) in pular1 ):
                        continue
                    else:
                        pular1.add(tuple(sorted((projeto1, projeto2))))
                    
                    if (debug):
                        print ("Tentando remover segundo projeto: projeto:", projeto2)
                        print ("Projetos já removidos:", [projeto1])
                        check = VerificaRestricoes(s_removed2, dados, f_removed2, gastos_removed2, desloc, sondas_removed2, max_free_removed2, total_free_removed2, total_setup_removed2, debug)
                        if (check):
                            check_str = "viável"
                        else:
                            check_str = "inviável"
                        print ("Solução atual: ", check_str)
                        PrintSolution(s_removed2)
                    
                    timer_remove.start()
                    s_removed2, flag2, node_janela, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, total_free_removed2, total_setup_removed2 = DesalocarProjetoPorNode(s_removed2, 
                                                                                    projeto2, node3_use, sonda1_use, desloc, 
                                                                                    dados, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, 
                                                                                    total_free_removed2, total_setup_removed2, debug)
                    timer_remove.stop()
                    
                    # se não conseguir remover, vai para o próximo node
                    if (flag2 == False):
                        continue
                    
                    if (debug):
                        print ("Projeto ", projeto2, " removido")
                        print ("Projetos já removidos:", [projeto1, projeto2])
                        check = VerificaRestricoes(s_removed2, dados, f_removed2, gastos_removed2, desloc, sondas_removed2, max_free_removed2, total_free_removed2, total_setup_removed2, debug)
                        if (check):
                            check_str = "viável"
                        else:
                            check_str = "inviável"
                        print ("Solução atual: ", check_str)
                        PrintSolution(s_removed2)
                    
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                    outfile = open(filename, 'wb')
                    pickle.dump(s_removed2, outfile)
                    outfile.close()
                    
                    # tentar inserir em outra sonda: enumerar
                    for el2 in shift_dict[projeto1]:
                        
                        if (el2[0] == -1):
                            _, sonda2, release2, due2 = el2
                            flag_el2 = "janela"
                        else:
                            projeto3, sonda2, _ = el2
                            flag_el2 = "projeto"
                        
                        aloc1 = False
                        
                        timer_copy.start()
                        #s_local1 = copy.deepcopy(s_removed2)
                        filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                        infile = open(filename, 'rb')
                        s_local1 = pickle.load(infile)
                        infile.close()
                        
                        gastos_local1 = copy.copy(gastos_removed2)
                        sondas_local1 = copy.deepcopy(sondas_removed2)
                        f_local1 = copy.copy(f_removed2)
                        max_free_local1 = copy.copy(max_free_removed2)
                        total_free_local1 = copy.copy(total_free_removed2)
                        total_setup_local1 = copy.copy(total_setup_removed2)
                        timer_copy.stop()
                        
                        tam_prev = [v for (v,k) in sondas_local1 if (k==sonda2)][0]
                        sondas_local1.remove((tam_prev, sonda2))
                        heapq.heapify(sondas_local1)
                        
                        if (debug):
                            print ("tam_prev da sonda", sonda2, " =", tam_prev)
                        
                        timer_find.start()
                        #if (flag_el2 == "janela"):
                        #    for node2_use in s_local1[sonda2]:
                        #        if ((release2 == node2_use.data[1]) and (due2 == node2_use.data[2])):
                        #            break
                        if (flag_el2 == "projeto"):
                            for node2_use in s_local1[sonda2]:
                                if (projeto3 == node2_use.data[0]):
                                    break
                        timer_find.stop()
                        
                        timer_insere.start()
                        #if (flag_el2 == "janela"):
                        #    aloc1, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeJanela(s_local1, node2_use, sonda2, projeto1, dados, lag, desloc, proc1, aloc1, gastos_local1, sondas_local1, f_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev, debug)
                        
                        if (flag_el2 == "projeto"):
                            aloc1, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeProjeto(s_local1, node2_use, sonda2, projeto1, dados, lag, desloc, proc1, aloc1, gastos_local1, f_local1, sondas_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev, debug)
                        timer_insere.stop()
                        
                        if (aloc1):
                            
                            if (debug):
                                print ("Projeto ", projeto1, " inserido na sonda ", sonda2)
                                print ("Projetos já removidos:", [projeto2])
                                check = VerificaRestricoes(s_local1, dados, f_local1, gastos_local1, desloc, sondas_local1, max_free_local1, total_free_local1, total_setup_local1, debug)
                                if (check):
                                    check_str = "viável"
                                else:
                                    check_str = "inviável"
                                print ("Solução atual: ", check_str)
                                PrintSolution(s_local1)
                            
                            tam_prev = [v for (v,k) in sondas_local1 if (k==sonda2)][0]
                            sondas_local1.remove((tam_prev, sonda2))
                            heapq.heapify(sondas_local1)
                            
                            if (debug):
                                print ("tam_prev da sonda2 =", tam_prev)
                            
                            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data4.pkl'
                            outfile = open(filename, 'wb')
                            pickle.dump(s_local1, outfile)
                            outfile.close()
                            
                            for el3 in shift_dict[projeto2]:
                                
                                if (el3[0] == -1):
                                    _, sonda3, release3, due3 = el3
                                    flag_el3 = "janela"
                                else:
                                    projeto4, sonda3, _ = el3
                                    flag_el3 = "projeto"
                                
                                if (sonda2 != sonda3):
                                    continue
                                
                                aloc2 = False
                                
                                timer_copy.start()
                                #s_local2 = copy.deepcopy(s_local1)
                                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data4.pkl'
                                infile = open(filename, 'rb')
                                s_local2 = pickle.load(infile)
                                infile.close()
                                
                                gastos_local2 = copy.copy(gastos_local1)
                                sondas_local2 = copy.deepcopy(sondas_local1)
                                f_local2 = copy.copy(f_local1)
                                max_free_local2 = copy.copy(max_free_local1)
                                total_free_local2 = copy.copy(total_free_local1)
                                total_setup_local2 = copy.copy(total_setup_local1)
                                timer_copy.stop()
                                
                                timer_find.start()
                                #if (flag_el3 == "janela"):
                                #    for node4_use in s_local2[sonda2]:
                                #        if ((release3 == node4_use.data[1]) and (due3 == node4_use.data[2])):
                                #            break
                                if (flag_el3 == "projeto"):
                                    for node4_use in s_local2[sonda2]:
                                        if (projeto4 == node4_use.data[0]):
                                            break
                                timer_find.stop()
                                
                                timer_insere.start()
                                #if (flag_el3 == "janela"):
                                #    aloc2, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeJanela(s_local2, node4_use, sonda2, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local2, sondas_local2, f_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev, debug)
                                
                                if (flag_el3 == "projeto"):
                                    aloc2, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeProjeto(s_local2, node4_use, sonda2, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local2, f_local2, sondas_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev, debug)
                                timer_insere.stop()
                                
                                if (aloc2):
                                    
                                    if (debug):
                                        print ("Projeto ", projeto2, " inserido na sonda ", sonda2)
                                        print ("Projetos já removidos:", [])
                                        check = VerificaRestricoes(s_local2, dados, f_local2, gastos_local2, desloc, sondas_local2, max_free_local2, total_free_local2, total_setup_local2, debug)
                                        if (check):
                                            check_str = "viável"
                                        else:
                                            check_str = "inviável"
                                        print ("Solução atual: ", check_str)
                                        PrintSolution(s_local1)
                                    
                                    if (total_free_local2 > total_free_best):

                                        if (debug):
                                            print ("Solução vizinha encontrada com melhor total_free")
                                            print ("sondas = ", sondas)

                                        s_best = copy.deepcopy(s_local2)
                                        gastos_best = copy.copy(gastos_local2)
                                        sondas_best = copy.deepcopy(sondas_local2)
                                        f_best = copy.copy(f_local2)
                                        max_free_best = copy.copy(max_free_local2)
                                        total_free_best = copy.copy(total_free_local2)
                                        total_setup_best = copy.copy(total_setup_local2)

                                    elif (total_free_local2 == total_free_best):

                                        if (-max_free_local2 > -max_free_best):

                                            if (debug):
                                                print ("Solução vizinha encontrada com melhor max_free")
                                                print ("sondas = ", sondas)

                                            s_best = copy.deepcopy(s_local2)
                                            gastos_best = copy.copy(gastos_local2)
                                            sondas_best = copy.deepcopy(sondas_local2)
                                            f_best = copy.copy(f_local2)
                                            max_free_best = copy.copy(max_free_local2)
                                            total_free_best = copy.copy(total_free_local2)
                                            total_setup_best = copy.copy(total_setup_local2)

                                        elif (-max_free_local2 == -max_free_best):

                                            if (total_setup_local2 < total_setup_best):

                                                if (debug):
                                                    print ("Solução vizinha encontrada com melhor total_setup")
                                                    print ("sondas = ", sondas)

                                                s_best = copy.deepcopy(s_local2)
                                                gastos_best = copy.copy(gastos_local2)
                                                sondas_best = copy.deepcopy(sondas_local2)
                                                f_best = copy.copy(f_local2)
                                                max_free_best = copy.copy(max_free_local2)
                                                total_free_best = copy.copy(total_free_local2)
                                                total_setup_best = copy.copy(total_setup_local2)
    
    tempo_total = timer_geral.get_time(reference = "total", unit = "seconds")
    tempo_find = timer_find.get_time(reference = "total", unit = "seconds")
    tempo_insere = timer_insere.get_time(reference = "total", unit = "seconds")
    tempo_remove = timer_remove.get_time(reference = "total", unit = "seconds")
    tempo_copy = timer_copy.get_time(reference = "total", unit = "seconds")
    tempos = (tempo_preproc, tempo_total, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if (debug):
        print ("Solução final tem:")
        print ("f =", f_best)
        print ("gastos =", gastos_best)
        print ("total_free =", total_free_best)
        print ("max_free =", max_free_best)
        print ("total_setup =", total_setup_best)
        print ("sondas:", sondas)
        print ("Tempo gasto no shift_2x0_interrota: ", tempo_total)
    
    return s_best, gastos_best, sondas_best, f_best, max_free_best, total_free_best, total_setup_best, tempos

def swap_1x1_interrota(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, debug=False, k=5):
    
    """
    Documentação: 
    
    Tenta trocar um projeto de uma sonda com um projeto de outra sonda.
    
    """
    
    if (debug):
        print ("Rodando estrutura de vizinhança: swap(1, 1)")
        print ("Solução inicial tem:")
        print ("f =", f)
        print ("gastos =", gastos)
        print ("total_free =", total_free)
        print ("max_free =", max_free)
        print ("total_setup =", total_setup)
        print ("sondas:", sondas)
    
    import pickle
    import copy
    import heapq
    import CPUtimer
    from time import process_time
    
    s_best = copy.deepcopy(s)
    gastos_best = copy.copy(gastos)
    sondas_best = copy.deepcopy(sondas)
    f_best = copy.copy(f)
    max_free_best = copy.copy(max_free)
    total_free_best = copy.copy(total_free)
    total_setup_best = copy.copy(total_setup)
    
    # gera conjunto de projetos já alocados
    proj_usados = set()
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_usados.add(node.data[0])
    
    # gera conjunto de projetos não alocados
    proj_nao_usados = set()
    for j in range(len(dados[4])):
        if j not in proj_usados:
            if (dados[19][j] > 0):
                proj_nao_usados.add(j)
    
    ans = PreProcessamento(s, desloc, dados, lag, proj_nao_usados, k=k, debug=debug)
    shift_dict, remove_dict, swap_dict, reinsert_dict, insert_fo_dict, swap_1x1_fo_dict, swap_1x2_fo_dict, swap_2x1_fo_dict, swap_2x2_fo_dict, tempo_preproc = ans
    
    timer_geral = CPUtimer.CPUTimer()
    timer_geral.reset()
    timer_geral.start()
    
    timer_find = CPUtimer.CPUTimer()
    timer_find.reset()
    
    timer_insere = CPUtimer.CPUTimer()
    timer_insere.reset()
    
    timer_remove = CPUtimer.CPUTimer()
    timer_remove.reset()
    
    timer_copy = CPUtimer.CPUTimer()
    timer_copy.reset()
    
    # otimização 1
    pular1 = set()
    
    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
    outfile = open(filename, 'wb')
    pickle.dump(s, outfile)
    outfile.close()
    
    # enumera todos os projetos que posso tentar remover
    for sonda1 in s.keys():
        for node1 in s[sonda1]:
            
            timer_copy.start()
            #s_removed1 = copy.deepcopy(s)
            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
            infile = open(filename, 'rb')
            s_removed1 = pickle.load(infile)
            infile.close()
            
            gastos_removed1 = copy.copy(gastos)
            sondas_removed1 = copy.deepcopy(sondas)
            f_removed1 = copy.copy(f)
            max_free_removed1 = copy.copy(max_free)
            total_free_removed1 = copy.copy(total_free)
            total_setup_removed1 = copy.copy(total_setup)
            timer_copy.stop()
            
            if (node1.data[0] != -1):
                
                timer_find.start()
                for node1_use in s_removed1[sonda1]:
                    if (node1.data[0] == node1_use.data[0]):
                        break
                timer_find.stop()
                
                timer_remove.start()
                # tenta remover
                projeto1 = node1.data[0]
                proc1 = dados[21][projeto1]
                s_removed1, flag1, node_janela, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, total_free_removed1, total_setup_removed1 = DesalocarProjetoPorNode(s_removed1, 
                                                                                projeto1, node1_use, sonda1, desloc, 
                                                                                dados, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, 
                                                                                total_free_removed1, total_setup_removed1, debug)
                timer_remove.stop()
                
                # se não conseguir remover, vai para o próximo node
                if (flag1 == False):
                    continue
                
                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                outfile = open(filename, 'wb')
                pickle.dump(s_removed1, outfile)
                outfile.close()
                
                # tentar trocar com outra sonda: enumerar
                for el1 in swap_dict[projeto1]:
                    
                    projeto2, sonda2, _ = el1
                    
                    timer_copy.start()
                    #s_removed2 = copy.deepcopy(s_removed1)
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                    infile = open(filename, 'rb')
                    s_removed2 = pickle.load(infile)
                    infile.close()
                    
                    gastos_removed2 = copy.copy(gastos_removed1)
                    sondas_removed2 = copy.deepcopy(sondas_removed1)
                    f_removed2 = copy.copy(f_removed1)
                    max_free_removed2 = copy.copy(max_free_removed1)
                    total_free_removed2 = copy.copy(total_free_removed1)
                    total_setup_removed2 = copy.copy(total_setup_removed1)
                    timer_copy.stop()
                    
                    timer_find.start()
                    for node2_use in s_removed2[sonda2]:
                        if (projeto2 == node2_use.data[0]):
                            break
                    timer_find.stop()
                    
                    # tenta remover
                    proc2 = dados[21][projeto2]
                    
                    # otimização 1
                    if ( tuple(sorted((projeto1, projeto2))) in pular1 ):
                        continue
                    else:
                        pular1.add(tuple(sorted((projeto1, projeto2))))
                    
                    timer_remove.start()
                    s_removed2, flag2, node_janela, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, total_free_removed2, total_setup_removed2 = DesalocarProjetoPorNode(s_removed2, 
                                                                                    projeto2, node2_use, sonda2, desloc, 
                                                                                    dados, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, 
                                                                                    total_free_removed2, total_setup_removed2, debug)
                    timer_remove.stop()
                    
                    # se não conseguir remover, vai para o próximo node
                    if (flag2 == False):
                        continue
                    
                    tam_prev2 = [v for (v,k) in sondas_removed2 if (k==sonda2)][0]
                    sondas_removed2.remove((tam_prev2, sonda2))
                    heapq.heapify(sondas_removed2)
                    
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                    outfile = open(filename, 'wb')
                    pickle.dump(s_removed2, outfile)
                    outfile.close()
                    
                    # tentar inserir projeto1 na sonda2: enumerar
                    for el2 in shift_dict[projeto1]:
                        
                        if (el2[0] == -1):
                            _, sonda3, release2, due2 = el2
                            flag_el2 = "janela"
                        else:
                            projeto3, sonda3, _ = el2
                            flag_el2 = "projeto"
                        
                        if (sonda2 != sonda3):
                            continue
                        
                        aloc1 = False
                        
                        timer_copy.start()
                        #s_local1 = copy.deepcopy(s_removed2)
                        filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                        infile = open(filename, 'rb')
                        s_local1 = pickle.load(infile)
                        infile.close()
                        
                        gastos_local1 = copy.copy(gastos_removed2)
                        sondas_local1 = copy.deepcopy(sondas_removed2)
                        f_local1 = copy.copy(f_removed2)
                        max_free_local1 = copy.copy(max_free_removed2)
                        total_free_local1 = copy.copy(total_free_removed2)
                        total_setup_local1 = copy.copy(total_setup_removed2)
                        timer_copy.stop()
                        
                        timer_find.start()
                        #if (flag_el2 == "janela"):
                        #    for node3_use in s_local1[sonda2]:
                        #        if ((release2 == node3_use.data[1]) and (due2 == node3_use.data[2])):
                        #            break
                        if (flag_el2 == "projeto"):
                            for node3_use in s_local1[sonda2]:
                                if (projeto3 == node3_use.data[0]):
                                    break
                        timer_find.stop()
                        
                        timer_insere.start()
                        #if (flag_el2 == "janela"):
                        #    aloc1, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeJanela(s_local1, node3_use, sonda2, projeto1, dados, lag, desloc, proc1, aloc1, gastos_local1, sondas_local1, f_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev2, debug)
                        
                        if (flag_el2 == "projeto"):
                            aloc1, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeProjeto(s_local1, node3_use, sonda2, projeto1, dados, lag, desloc, proc1, aloc1, gastos_local1, f_local1, sondas_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev2, debug)
                        timer_insere.stop()
                        
                        if (aloc1):
                            
                            tam_prev1 = [v for (v,k) in sondas_local1 if (k==sonda1)][0]
                            sondas_local1.remove((tam_prev1, sonda1))
                            heapq.heapify(sondas_local1)
                            
                            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data4.pkl'
                            outfile = open(filename, 'wb')
                            pickle.dump(s_local1, outfile)
                            outfile.close()
                            
                            # tentar inserir projeto2 na sonda1: enumerar
                            for el3 in shift_dict[projeto2]:
                                
                                if (el3[0] == -1):
                                    _, sonda4, release3, due3 = el3
                                    flag_el3 = "janela"
                                else:
                                    projeto4, sonda4, _ = el3
                                    flag_el3 = "projeto"
                                
                                if (sonda1 != sonda4):
                                    continue
                                
                                aloc2 = False
                                
                                timer_copy.start()
                                #s_local2 = copy.deepcopy(s_local1)
                                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data4.pkl'
                                infile = open(filename, 'rb')
                                s_local2 = pickle.load(infile)
                                infile.close()
                                
                                gastos_local2 = copy.copy(gastos_local1)
                                sondas_local2 = copy.deepcopy(sondas_local1)
                                f_local2 = copy.copy(f_local1)
                                max_free_local2 = copy.copy(max_free_local1)
                                total_free_local2 = copy.copy(total_free_local1)
                                total_setup_local2 = copy.copy(total_setup_local1)
                                timer_copy.stop()
                                
                                timer_find.start()
                                #if (flag_el3 == "janela"):
                                #    for node4_use in s_local2[sonda1]:
                                #        if ((release3 == node4_use.data[1]) and (due3 == node4_use.data[2])):
                                #            break
                                if (flag_el3 == "projeto"):
                                    for node4_use in s_local2[sonda1]:
                                        if (projeto4 == node4_use.data[0]):
                                            break
                                timer_find.stop()
                                
                                timer_insere.start()
                                #if (flag_el3 == "janela"):
                                #    aloc2, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeJanela(s_local2, node4_use, sonda1, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local2, sondas_local2, f_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev1, debug)
                                
                                if (flag_el3 == "projeto"):
                                    aloc2, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeProjeto(s_local2, node4_use, sonda1, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local2, f_local2, sondas_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev1, debug)
                                timer_insere.stop()
                                
                                if (aloc2):

                                    if (total_free_local2 > total_free_best):

                                        if (debug):
                                            print ("Solução vizinha encontrada com melhor total_free")

                                        s_best = copy.deepcopy(s_local2)
                                        gastos_best = copy.copy(gastos_local2)
                                        sondas_best = copy.deepcopy(sondas_local2)
                                        f_best = copy.copy(f_local2)
                                        max_free_best = copy.copy(max_free_local2)
                                        total_free_best = copy.copy(total_free_local2)
                                        total_setup_best = copy.copy(total_setup_local2)

                                    elif (total_free_local2 == total_free_best):

                                        if (-max_free_local2 > -max_free_best):

                                            if (debug):
                                                print ("Solução vizinha encontrada com melhor max_free")

                                            s_best = copy.deepcopy(s_local2)
                                            gastos_best = copy.copy(gastos_local2)
                                            sondas_best = copy.deepcopy(sondas_local2)
                                            f_best = copy.copy(f_local2)
                                            max_free_best = copy.copy(max_free_local2)
                                            total_free_best = copy.copy(total_free_local2)
                                            total_setup_best = copy.copy(total_setup_local2)

                                        elif (-max_free_local2 == -max_free_best):

                                            if (total_setup_local2 < total_setup_best):

                                                if (debug):
                                                    print ("Solução vizinha encontrada com melhor total_setup")

                                                s_best = copy.deepcopy(s_local2)
                                                gastos_best = copy.copy(gastos_local2)
                                                sondas_best = copy.deepcopy(sondas_local2)
                                                f_best = copy.copy(f_local2)
                                                max_free_best = copy.copy(max_free_local2)
                                                total_free_best = copy.copy(total_free_local2)
                                                total_setup_best = copy.copy(total_setup_local2)
    
    tempo_total = timer_geral.get_time(reference = "total", unit = "seconds")
    tempo_find = timer_find.get_time(reference = "total", unit = "seconds")
    tempo_insere = timer_insere.get_time(reference = "total", unit = "seconds")
    tempo_remove = timer_remove.get_time(reference = "total", unit = "seconds")
    tempo_copy = timer_copy.get_time(reference = "total", unit = "seconds")
    tempos = (tempo_preproc, tempo_total, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if (debug):
        print ("Solução final tem:")
        print ("f =", f_best)
        print ("gastos =", gastos_best)
        print ("total_free =", total_free_best)
        print ("max_free =", max_free_best)
        print ("total_setup =", total_setup_best)
        print ("sondas:", sondas)
        print ("Tempo gasto no swap_1x1_interrota: ", tempo_total)
    
    return s_best, gastos_best, sondas_best, f_best, max_free_best, total_free_best, total_setup_best, tempos

def swap_2x1_interrota(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, debug=False, k=5):
    
    """
    Documentação: 
    
    Tenta trocar dois projetos de uma sonda com um projeto de outra sonda.
    
    """
    
    if (debug):
        print ("Rodando estrutura de vizinhança: swap(2, 1)")
        print ("Solução inicial tem:")
        print ("f =", f)
        print ("gastos =", gastos)
        print ("total_free =", total_free)
        print ("max_free =", max_free)
        print ("total_setup =", total_setup)
        print ("sondas:", sondas)
    
    import pickle
    import copy
    import heapq
    import CPUtimer
    from time import process_time
    
    s_best = copy.deepcopy(s)
    gastos_best = copy.copy(gastos)
    sondas_best = copy.deepcopy(sondas)
    f_best = copy.copy(f)
    max_free_best = copy.copy(max_free)
    total_free_best = copy.copy(total_free)
    total_setup_best = copy.copy(total_setup)
    
    # gera conjunto de projetos já alocados
    proj_usados = set()
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_usados.add(node.data[0])
    
    # gera conjunto de projetos não alocados
    proj_nao_usados = set()
    for j in range(len(dados[4])):
        if j not in proj_usados:
            if (dados[19][j] > 0):
                proj_nao_usados.add(j)
    
    ans = PreProcessamento(s, desloc, dados, lag, proj_nao_usados, k=k, debug=debug)
    shift_dict, remove_dict, swap_dict, reinsert_dict, insert_fo_dict, swap_1x1_fo_dict, swap_1x2_fo_dict, swap_2x1_fo_dict, swap_2x2_fo_dict, tempo_preproc = ans
    
    timer_geral = CPUtimer.CPUTimer()
    timer_geral.reset()
    timer_geral.start()
    
    timer_find = CPUtimer.CPUTimer()
    timer_find.reset()
    
    timer_insere = CPUtimer.CPUTimer()
    timer_insere.reset()
    
    timer_remove = CPUtimer.CPUTimer()
    timer_remove.reset()
    
    timer_copy = CPUtimer.CPUTimer()
    timer_copy.reset()
    
    # otimização 1
    pular1 = set()
    pular2 = set()
    
    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
    outfile = open(filename, 'wb')
    pickle.dump(s, outfile)
    outfile.close()
    
    # enumera todos os projetos que posso tentar remover
    for sonda1 in s.keys():
        for node1 in s[sonda1]:
            
            timer_copy.start()
            #s_removed1 = copy.deepcopy(s)
            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
            infile = open(filename, 'rb')
            s_removed1 = pickle.load(infile)
            infile.close()
            
            gastos_removed1 = copy.copy(gastos)
            sondas_removed1 = copy.deepcopy(sondas)
            f_removed1 = copy.copy(f)
            max_free_removed1 = copy.copy(max_free)
            total_free_removed1 = copy.copy(total_free)
            total_setup_removed1 = copy.copy(total_setup)
            timer_copy.stop()
            
            if (node1.data[0] != -1):
                
                timer_find.start()
                for node1_use in s_removed1[sonda1]:
                    if (node1.data[0] == node1_use.data[0]):
                        break
                timer_find.stop()
                
                timer_remove.start()
                # tenta remover projeto 1 da sonda 1
                projeto1 = node1.data[0]
                proc1 = dados[21][projeto1]
                s_removed1, flag1, node_janela, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, total_free_removed1, total_setup_removed1 = DesalocarProjetoPorNode(s_removed1, 
                                                                                projeto1, node1_use, sonda1, desloc, 
                                                                                dados, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, 
                                                                                total_free_removed1, total_setup_removed1, debug)
                timer_remove.stop()
                
                # se não conseguir remover, vai para o próximo node
                if (flag1 == False):
                    continue
                
                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                outfile = open(filename, 'wb')
                pickle.dump(s_removed1, outfile)
                outfile.close()
                
                for el1 in remove_dict[projeto1]:
                    
                    projeto2, _, _ = el1
                    
                    timer_copy.start()
                    #s_removed2 = copy.deepcopy(s_removed1)
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                    infile = open(filename, 'rb')
                    s_removed2 = pickle.load(infile)
                    infile.close()
                    
                    gastos_removed2 = copy.copy(gastos_removed1)
                    sondas_removed2 = copy.deepcopy(sondas_removed1)
                    f_removed2 = copy.copy(f_removed1)
                    max_free_removed2 = copy.copy(max_free_removed1)
                    total_free_removed2 = copy.copy(total_free_removed1)
                    total_setup_removed2 = copy.copy(total_setup_removed1)
                    timer_copy.stop()
                    
                    timer_find.start()
                    for node2_use in s_removed2[sonda1]:
                        if (projeto2 == node2_use.data[0]):
                            break
                    timer_find.stop()
                    
                    # tenta remover projeto 2 da sonda 1
                    proc2 = dados[21][projeto2]
                    
                    # otimização 1
                    if ( tuple(sorted((projeto1, projeto2))) in pular1 ):
                        continue
                    else:
                        pular1.add(tuple(sorted((projeto1, projeto2))))
                    
                    timer_remove.start()
                    s_removed2, flag2, node_janela, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, total_free_removed2, total_setup_removed2 = DesalocarProjetoPorNode(s_removed2, 
                                                                                    projeto2, node2_use, sonda1, desloc, 
                                                                                    dados, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, 
                                                                                    total_free_removed2, total_setup_removed2, debug)
                    timer_remove.stop()
                    
                    # se não conseguir remover, vai para o próximo node
                    if (flag2 == False):
                        continue
                    
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                    outfile = open(filename, 'wb')
                    pickle.dump(s_removed2, outfile)
                    outfile.close()
                    
                    # proxima sonda
                    for el2 in swap_dict[projeto1]:
                        
                        projeto3, sonda2, _ = el2
                        
                        timer_copy.start()
                        #s_removed3 = copy.deepcopy(s_removed2)
                        filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                        infile = open(filename, 'rb')
                        s_removed3 = pickle.load(infile)
                        infile.close()
                        
                        gastos_removed3 = copy.copy(gastos_removed2)
                        sondas_removed3 = copy.deepcopy(sondas_removed2)
                        f_removed3 = copy.copy(f_removed2)
                        max_free_removed3 = copy.copy(max_free_removed2)
                        total_free_removed3 = copy.copy(total_free_removed2)
                        total_setup_removed3 = copy.copy(total_setup_removed2)
                        timer_copy.stop()
                        
                        timer_find.start()
                        for node3_use in s_removed3[sonda2]:
                            if (projeto3 == node3_use.data[0]):
                                break
                        timer_find.stop()
                        
                        # tenta remover projeto 3 da sonda 2
                        proc3 = dados[21][projeto3]
                        
                        # otimização 1
                        if ( tuple(sorted((projeto1, projeto2, projeto3))) in pular2 ):
                            continue
                        else:
                            pular2.add(tuple(sorted((projeto1, projeto2, projeto3))))
                        
                        timer_remove.start()
                        s_removed3, flag3, node_janela, gastos_removed3, sondas_removed3, f_removed3, max_free_removed3, total_free_removed3, total_setup_removed3 = DesalocarProjetoPorNode(s_removed3, 
                                                                                        projeto3, node3_use, sonda2, desloc, 
                                                                                        dados, gastos_removed3, sondas_removed3, f_removed3, max_free_removed3, 
                                                                                        total_free_removed3, total_setup_removed3, debug)
                        timer_remove.stop()
                        
                        # se não conseguir remover, vai para o próximo node
                        if (flag3 == False):
                            continue
                        
                        filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data4.pkl'
                        outfile = open(filename, 'wb')
                        pickle.dump(s_removed3, outfile)
                        outfile.close()
                        
                        # tentar inserir projeto1 na sonda2: enumerar
                        for el3 in shift_dict[projeto1]:
                            
                            if (el3[0] == -1):
                                _, sonda3, release3, due3 = el3
                                flag_el3 = "janela"
                            else:
                                projeto4, sonda3, _ = el3
                                flag_el3 = "projeto"
                            
                            if (sonda2 != sonda3):
                                continue
                            
                            aloc1 = False
                            
                            timer_copy.start()
                            #s_local1 = copy.deepcopy(s_removed3)
                            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data4.pkl'
                            infile = open(filename, 'rb')
                            s_local1 = pickle.load(infile)
                            infile.close()
                            
                            gastos_local1 = copy.copy(gastos_removed3)
                            sondas_local1 = copy.deepcopy(sondas_removed3)
                            f_local1 = copy.copy(f_removed3)
                            max_free_local1 = copy.copy(max_free_removed3)
                            total_free_local1 = copy.copy(total_free_removed3)
                            total_setup_local1 = copy.copy(total_setup_removed3)
                            timer_copy.stop()
                            
                            tam_prev2 = [v for (v,k) in sondas_local1 if (k==sonda2)][0]
                            sondas_local1.remove((tam_prev2, sonda2))
                            heapq.heapify(sondas_local1)
                            
                            timer_find.start()
                            #if (flag_el3 == "janela"):
                            #    for node4_use in s_local1[sonda2]:
                            #        if ((release3 == node4_use.data[1]) and (due3 == node4_use.data[2])):
                            #            break
                            if (flag_el3 == "projeto"):
                                for node4_use in s_local1[sonda2]:
                                    if (projeto4 == node4_use.data[0]):
                                        break
                            timer_find.stop()
                            
                            timer_insere.start()
                            #if (flag_el3 == "janela"):
                            #    aloc1, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeJanela(s_local1, node4_use, sonda2, projeto1, dados, lag, desloc, proc1, aloc1, gastos_local1, sondas_local1, f_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev2, debug)
                            
                            if (flag_el3 == "projeto"):
                                aloc1, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeProjeto(s_local1, node4_use, sonda2, projeto1, dados, lag, desloc, proc1, aloc1, gastos_local1, f_local1, sondas_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev2, debug)
                            timer_insere.stop()
                            
                            if (aloc1):
                                
                                # atualiza tam_prev
                                tam_prev2 = [v for (v,k) in sondas_local1 if (k==sonda2)][0]
                                sondas_local1.remove((tam_prev2, sonda2))
                                heapq.heapify(sondas_local1)
                                
                                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data5.pkl'
                                outfile = open(filename, 'wb')
                                pickle.dump(s_local1, outfile)
                                outfile.close()
                                
                                # tentar inserir projeto2 na sonda2: enumerar
                                for el4 in shift_dict[projeto2]:
                                    
                                    if (el4[0] == -1):
                                        _, sonda4, release4, due4 = el4
                                        flag_el4 = "janela"
                                    else:
                                        projeto5, sonda4, _ = el4
                                        flag_el4 = "projeto"
                                    
                                    if (sonda2 != sonda4):
                                        continue
                                    
                                    aloc2 = False
                                    
                                    timer_copy.start()
                                    #s_local2 = copy.deepcopy(s_local1)
                                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data5.pkl'
                                    infile = open(filename, 'rb')
                                    s_local2 = pickle.load(infile)
                                    infile.close()
                                    
                                    gastos_local2 = copy.copy(gastos_local1)
                                    sondas_local2 = copy.deepcopy(sondas_local1)
                                    f_local2 = copy.copy(f_local1)
                                    max_free_local2 = copy.copy(max_free_local1)
                                    total_free_local2 = copy.copy(total_free_local1)
                                    total_setup_local2 = copy.copy(total_setup_local1)
                                    timer_copy.stop()
                                    
                                    timer_find.start()
                                    #if (flag_el4 == "janela"):
                                    #    for node5_use in s_local2[sonda2]:
                                    #        if ((release4 == node5_use.data[1]) and (due4 == node5_use.data[2])):
                                    #            break
                                    if (flag_el4 == "projeto"):
                                        for node5_use in s_local2[sonda2]:
                                            if (projeto5 == node5_use.data[0]):
                                                break
                                    timer_find.stop()
                                    
                                    timer_insere.start()
                                    #if (flag_el4 == "janela"):
                                    #    aloc2, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeJanela(s_local2, node5_use, sonda2, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local2, sondas_local2, f_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev2, debug)
                                    
                                    if (flag_el4 == "projeto"):
                                        aloc2, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeProjeto(s_local2, node5_use, sonda2, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local2, f_local2, sondas_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev2, debug)
                                    timer_insere.stop()
                                    
                                    if (aloc2):
                                        
                                        tam_prev1 = [v for (v,k) in sondas_local2 if (k==sonda1)][0]
                                        sondas_local2.remove((tam_prev1, sonda1))
                                        heapq.heapify(sondas_local2)
                                        
                                        filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data6.pkl'
                                        outfile = open(filename, 'wb')
                                        pickle.dump(s_local2, outfile)
                                        outfile.close()
                                        
                                        # tentar inserir projeto3 na sonda1: enumerar
                                        for el5 in shift_dict[projeto3]:
                                            
                                            if (el5[0] == -1):
                                                _, sonda5, release5, due5 = el5
                                                flag_el5 = "janela"
                                            else:
                                                projeto6, sonda5, _ = el5
                                                flag_el5 = "projeto"
                                            
                                            if (sonda1 != sonda5):
                                                continue
                                            
                                            aloc3 = False
                                            
                                            timer_copy.start()
                                            #s_local3 = copy.deepcopy(s_local2)
                                            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data6.pkl'
                                            infile = open(filename, 'rb')
                                            s_local3 = pickle.load(infile)
                                            infile.close()
                                            
                                            gastos_local3 = copy.copy(gastos_local2)
                                            sondas_local3 = copy.deepcopy(sondas_local2)
                                            f_local3 = copy.copy(f_local2)
                                            max_free_local3 = copy.copy(max_free_local2)
                                            total_free_local3 = copy.copy(total_free_local2)
                                            total_setup_local3 = copy.copy(total_setup_local2)
                                            timer_copy.stop()
                                            
                                            timer_find.start()
                                            #if (flag_el5 == "janela"):
                                            #    for node6_use in s_local3[sonda1]:
                                            #        if ((release5 == node6_use.data[1]) and (due5 == node6_use.data[2])):
                                            #            break
                                            if (flag_el5 == "projeto"):
                                                for node6_use in s_local3[sonda1]:
                                                    if (projeto6 == node6_use.data[0]):
                                                        break
                                            timer_find.stop()
                                            
                                            timer_insere.start()
                                            #if (flag_el5 == "janela"):
                                            #    aloc3, gastos_local3, sondas_local3, f_local3, total_free_local3, total_setup_local3, max_free_local3 = TentaInserirNodeDeJanela(s_local3, node6_use, sonda1, projeto3, dados, lag, desloc, proc3, aloc3, gastos_local3, sondas_local3, f_local3, max_free_local3, total_free_local3, total_setup_local3, tam_prev1, debug)
                                            
                                            if (flag_el5 == "projeto"):
                                                aloc3, gastos_local3, sondas_local3, f_local3, total_free_local3, total_setup_local3, max_free_local3 = TentaInserirNodeDeProjeto(s_local3, node6_use, sonda1, projeto3, dados, lag, desloc, proc3, aloc3, gastos_local3, f_local3, sondas_local3, max_free_local3, total_free_local3, total_setup_local3, tam_prev1, debug)
                                            timer_insere.stop()
                                            
                                            if (aloc3):

                                                if (total_free_local3 > total_free_best):

                                                    if (debug):
                                                        print ("Solução vizinha encontrada com melhor total_free")

                                                    s_best = copy.deepcopy(s_local3)
                                                    gastos_best = copy.copy(gastos_local3)
                                                    sondas_best = copy.deepcopy(sondas_local3)
                                                    f_best = copy.copy(f_local3)
                                                    max_free_best = copy.copy(max_free_local3)
                                                    total_free_best = copy.copy(total_free_local3)
                                                    total_setup_best = copy.copy(total_setup_local3)

                                                elif (total_free_local3 == total_free_best):

                                                    if (-max_free_local3 > -max_free_best):

                                                        if (debug):
                                                            print ("Solução vizinha encontrada com melhor max_free")

                                                        s_best = copy.deepcopy(s_local3)
                                                        gastos_best = copy.copy(gastos_local3)
                                                        sondas_best = copy.deepcopy(sondas_local3)
                                                        f_best = copy.copy(f_local3)
                                                        max_free_best = copy.copy(max_free_local3)
                                                        total_free_best = copy.copy(total_free_local3)
                                                        total_setup_best = copy.copy(total_setup_local3)

                                                    elif (-max_free_local3 == -max_free_best):

                                                        if (total_setup_local3 < total_setup_best):

                                                            if (debug):
                                                                print ("Solução vizinha encontrada com melhor total_setup")

                                                            s_best = copy.deepcopy(s_local3)
                                                            gastos_best = copy.copy(gastos_local3)
                                                            sondas_best = copy.deepcopy(sondas_local3)
                                                            f_best = copy.copy(f_local3)
                                                            max_free_best = copy.copy(max_free_local3)
                                                            total_free_best = copy.copy(total_free_local3)
                                                            total_setup_best = copy.copy(total_setup_local3)
    
    tempo_total = timer_geral.get_time(reference = "total", unit = "seconds")
    tempo_find = timer_find.get_time(reference = "total", unit = "seconds")
    tempo_insere = timer_insere.get_time(reference = "total", unit = "seconds")
    tempo_remove = timer_remove.get_time(reference = "total", unit = "seconds")
    tempo_copy = timer_copy.get_time(reference = "total", unit = "seconds")
    tempos = (tempo_preproc, tempo_total, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if (debug):
        print ("Solução final tem:")
        print ("f =", f_best)
        print ("gastos =", gastos_best)
        print ("total_free =", total_free_best)
        print ("max_free =", max_free_best)
        print ("total_setup =", total_setup_best)
        print ("sondas:", sondas)
        print ("Tempo gasto no swap_2x1_interrota: ", tempo_total)
    
    return s_best, gastos_best, sondas_best, f_best, max_free_best, total_free_best, total_setup_best, tempos

def swap_2x2_interrota(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, debug=False, k=5):
    
    """
    Documentação: 
    
    Tenta trocar dois projetos de uma sonda com dois projetos de outra sonda.
    
    """
    
    if (debug):
        print ("Rodando estrutura de vizinhança: swap(2, 2)")
        print ("Solução inicial tem:")
        print ("f =", f)
        print ("gastos =", gastos)
        print ("total_free =", total_free)
        print ("max_free =", max_free)
        print ("total_setup =", total_setup)
        print ("sondas:", sondas)
    
    import pickle
    import copy
    import heapq
    import CPUtimer
    from time import process_time
    
    s_best = copy.deepcopy(s)
    gastos_best = copy.copy(gastos)
    sondas_best = copy.deepcopy(sondas)
    f_best = copy.copy(f)
    max_free_best = copy.copy(max_free)
    total_free_best = copy.copy(total_free)
    total_setup_best = copy.copy(total_setup)
    
    # gera conjunto de projetos já alocados
    proj_usados = set()
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_usados.add(node.data[0])
    
    # gera conjunto de projetos não alocados
    proj_nao_usados = set()
    for j in range(len(dados[4])):
        if j not in proj_usados:
            if (dados[19][j] > 0):
                proj_nao_usados.add(j)
    
    ans = PreProcessamento(s, desloc, dados, lag, proj_nao_usados, k=k, debug=debug)
    shift_dict, remove_dict, swap_dict, reinsert_dict, insert_fo_dict, swap_1x1_fo_dict, swap_1x2_fo_dict, swap_2x1_fo_dict, swap_2x2_fo_dict, tempo_preproc = ans
    
    timer_geral = CPUtimer.CPUTimer()
    timer_geral.reset()
    timer_geral.start()
    
    timer_find = CPUtimer.CPUTimer()
    timer_find.reset()
    
    timer_insere = CPUtimer.CPUTimer()
    timer_insere.reset()
    
    timer_remove = CPUtimer.CPUTimer()
    timer_remove.reset()
    
    timer_copy = CPUtimer.CPUTimer()
    timer_copy.reset()
    
    # otimização 1
    pular1 = set()
    pular2 = set()
    pular3 = set()
    
    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
    outfile = open(filename, 'wb')
    pickle.dump(s, outfile)
    outfile.close()
    
    # enumera todos os projetos que posso tentar remover
    for sonda1 in s.keys():
        for node1 in s[sonda1]:
            
            timer_copy.start()
            #s_removed1 = copy.deepcopy(s)
            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
            infile = open(filename, 'rb')
            s_removed1 = pickle.load(infile)
            infile.close()
            
            gastos_removed1 = copy.copy(gastos)
            sondas_removed1 = copy.deepcopy(sondas)
            f_removed1 = copy.copy(f)
            max_free_removed1 = copy.copy(max_free)
            total_free_removed1 = copy.copy(total_free)
            total_setup_removed1 = copy.copy(total_setup)
            timer_copy.stop()
            
            if (node1.data[0] != -1):
                
                timer_find.start()
                for node1_use in s_removed1[sonda1]:
                    if (node1.data[0] == node1_use.data[0]):
                        break
                timer_find.stop()
                
                timer_remove.start()
                # tenta remover projeto 1 da sonda 1
                projeto1 = node1.data[0]
                proc1 = dados[21][projeto1]
                s_removed1, flag1, node_janela, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, total_free_removed1, total_setup_removed1 = DesalocarProjetoPorNode(s_removed1, 
                                                                                projeto1, node1_use, sonda1, desloc, 
                                                                                dados, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, 
                                                                                total_free_removed1, total_setup_removed1, debug)
                timer_remove.stop()
                
                # se não conseguir remover, vai para o próximo node
                if (flag1 == False):
                    continue
                
                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                outfile = open(filename, 'wb')
                pickle.dump(s_removed1, outfile)
                outfile.close()
    
                for el1 in remove_dict[projeto1]:
                    
                    projeto2, _, _ = el1
                    
                    timer_copy.start()
                    #s_removed2 = copy.deepcopy(s_removed1)
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                    infile = open(filename, 'rb')
                    s_removed2 = pickle.load(infile)
                    infile.close()
                    
                    gastos_removed2 = copy.copy(gastos_removed1)
                    sondas_removed2 = copy.deepcopy(sondas_removed1)
                    f_removed2 = copy.copy(f_removed1)
                    max_free_removed2 = copy.copy(max_free_removed1)
                    total_free_removed2 = copy.copy(total_free_removed1)
                    total_setup_removed2 = copy.copy(total_setup_removed1)
                    timer_copy.stop()
                    
                    timer_find.start()
                    for node2_use in s_removed2[sonda1]:
                        if (projeto2 == node2_use.data[0]):
                            break
                    timer_find.stop()
                    
                    # tenta remover projeto 2 da sonda 1
                    proc2 = dados[21][projeto2]
                    
                    # otimização 1
                    if ( tuple(sorted((projeto1, projeto2))) in pular1 ):
                        continue
                    else:
                        pular1.add(tuple(sorted((projeto1, projeto2))))
                    
                    timer_remove.start()
                    s_removed2, flag2, node_janela, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, total_free_removed2, total_setup_removed2 = DesalocarProjetoPorNode(s_removed2, 
                                                                                    projeto2, node2_use, sonda1, desloc, 
                                                                                    dados, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, 
                                                                                    total_free_removed2, total_setup_removed2, debug)
                    timer_remove.stop()
                    
                    # se não conseguir remover, vai para o próximo node
                    if (flag2 == False):
                        continue
                    
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                    outfile = open(filename, 'wb')
                    pickle.dump(s_removed2, outfile)
                    outfile.close()
                    
                    # proxima sonda
                    for el2 in swap_dict[projeto1]:
                        
                        projeto3, sonda2, _, = el2
                        
                        timer_copy.start()
                        #s_removed3 = copy.deepcopy(s_removed2)
                        filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                        infile = open(filename, 'rb')
                        s_removed3 = pickle.load(infile)
                        infile.close()
                        
                        gastos_removed3 = copy.copy(gastos_removed2)
                        sondas_removed3 = copy.deepcopy(sondas_removed2)
                        f_removed3 = copy.copy(f_removed2)
                        max_free_removed3 = copy.copy(max_free_removed2)
                        total_free_removed3 = copy.copy(total_free_removed2)
                        total_setup_removed3 = copy.copy(total_setup_removed2)
                        timer_copy.stop()
                        
                        timer_find.start()
                        for node3_use in s_removed3[sonda2]:
                            if (projeto3 == node3_use.data[0]):
                                break
                        timer_find.stop()
                        
                        # tenta remover projeto 3 da sonda 2
                        proc3 = dados[21][projeto3]
                        
                        # otimização 1
                        if ( tuple(sorted((projeto1, projeto2, projeto3))) in pular2 ):
                            continue
                        else:
                            pular2.add(tuple(sorted((projeto1, projeto2, projeto3))))
                        
                        timer_remove.start()
                        s_removed3, flag3, node_janela, gastos_removed3, sondas_removed3, f_removed3, max_free_removed3, total_free_removed3, total_setup_removed3 = DesalocarProjetoPorNode(s_removed3, 
                                                                                        projeto3, node3_use, sonda2, desloc, 
                                                                                        dados, gastos_removed3, sondas_removed3, f_removed3, max_free_removed3, 
                                                                                        total_free_removed3, total_setup_removed3, debug)
                        timer_remove.stop()
                        
                        # se não conseguir remover, vai para o próximo node
                        if (flag3 == False):
                            continue
                        
                        filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data4.pkl'
                        outfile = open(filename, 'wb')
                        pickle.dump(s_removed3, outfile)
                        outfile.close()
                        
                        for el3 in remove_dict[projeto3]:
                            
                            projeto4, _, _ = el3
                            
                            timer_copy.start()
                            #s_removed4 = copy.deepcopy(s_removed3)
                            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data4.pkl'
                            infile = open(filename, 'rb')
                            s_removed4 = pickle.load(infile)
                            infile.close()
                            
                            gastos_removed4 = copy.copy(gastos_removed3)
                            sondas_removed4 = copy.deepcopy(sondas_removed3)
                            f_removed4 = copy.copy(f_removed3)
                            max_free_removed4 = copy.copy(max_free_removed3)
                            total_free_removed4 = copy.copy(total_free_removed3)
                            total_setup_removed4 = copy.copy(total_setup_removed3)
                            timer_copy.stop()
                            
                            timer_find.start()
                            for node4_use in s_removed4[sonda2]:
                                if (projeto4 == node4_use.data[0]):
                                    break
                            timer_find.stop()
                            
                            # tenta remover projeto 4 da sonda 2
                            proc4 = dados[21][projeto4]
                            
                            # otimização 1
                            if ( tuple(sorted((projeto1, projeto2, projeto3, projeto4))) in pular3 ):
                                continue
                            else:
                                pular3.add(tuple(sorted((projeto1, projeto2, projeto3, projeto4))))
                            
                            timer_remove.start()
                            s_removed4, flag4, node_janela, gastos_removed4, sondas_removed4, f_removed4, max_free_removed4, total_free_removed4, total_setup_removed4 = DesalocarProjetoPorNode(s_removed4, 
                                                                                            projeto4, node4_use, sonda2, desloc, 
                                                                                            dados, gastos_removed4, sondas_removed4, f_removed4, max_free_removed4, 
                                                                                            total_free_removed4, total_setup_removed4, debug)
                            timer_remove.stop()
                            
                            # se não conseguir remover, vai para o próximo node
                            if (flag4 == False):
                                continue
                            
                            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data5.pkl'
                            outfile = open(filename, 'wb')
                            pickle.dump(s_removed4, outfile)
                            outfile.close()
                            
                            # tentar inserir projeto1 na sonda2: enumerar
                            for el4 in shift_dict[projeto1]:
                                
                                if (el4[0] == -1):
                                    _, sonda3, release4, due4 = el4
                                    flag_el4 = "janela"
                                else:
                                    projeto5, sonda3, _ = el4
                                    flag_el4 = "projeto"
                                
                                if (sonda2 != sonda3):
                                    continue
                                
                                aloc1 = False
                                
                                timer_copy.start()
                                #s_local1 = copy.deepcopy(s_removed4)
                                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data5.pkl'
                                infile = open(filename, 'rb')
                                s_local1 = pickle.load(infile)
                                infile.close()
                                
                                gastos_local1 = copy.copy(gastos_removed4)
                                sondas_local1 = copy.deepcopy(sondas_removed4)
                                f_local1 = copy.copy(f_removed4)
                                max_free_local1 = copy.copy(max_free_removed4)
                                total_free_local1 = copy.copy(total_free_removed4)
                                total_setup_local1 = copy.copy(total_setup_removed4)
                                timer_copy.stop()
                                
                                tam_prev2 = [v for (v,k) in sondas_local1 if (k==sonda2)][0]
                                sondas_local1.remove((tam_prev2, sonda2))
                                heapq.heapify(sondas_local1)
                                
                                timer_find.start()
                                #if (flag_el4 == "janela"):
                                #    for node5_use in s_local1[sonda2]:
                                #        if ((release4 == node5_use.data[1]) and (due4 == node5_use.data[2])):
                                #            break
                                if (flag_el4 == "projeto"):
                                    for node5_use in s_local1[sonda2]:
                                        if (projeto5 == node5_use.data[0]):
                                            break
                                timer_find.stop()
                                
                                timer_insere.start()
                                #if (flag_el4 == "janela"):
                                #    aloc1, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeJanela(s_local1, node5_use, sonda2, projeto1, dados, lag, desloc, proc1, aloc1, gastos_local1, sondas_local1, f_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev2, debug)
                                
                                if (flag_el4 == "projeto"):
                                    aloc1, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeProjeto(s_local1, node5_use, sonda2, projeto1, dados, lag, desloc, proc1, aloc1, gastos_local1, f_local1, sondas_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev2, debug)
                                timer_insere.stop()
                                
                                if (aloc1):
                                    
                                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data6.pkl'
                                    outfile = open(filename, 'wb')
                                    pickle.dump(s_local1, outfile)
                                    outfile.close()
                                    
                                    # tentar inserir projeto2 na sonda2: enumerar
                                    for el5 in shift_dict[projeto2]:
                                        
                                        if (el5[0] == -1):
                                            _, sonda4, release5, due5 = el5
                                            flag_el5 = "janela"
                                        else:
                                            projeto6, sonda4, _ = el5
                                            flag_el5 = "projeto"
                                        
                                        if (sonda2 != sonda4):
                                            continue
                                        
                                        aloc2 = False
                                        
                                        timer_copy.start()
                                        #s_local2 = copy.deepcopy(s_local1)
                                        filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data6.pkl'
                                        infile = open(filename, 'rb')
                                        s_local2 = pickle.load(infile)
                                        infile.close()
                                        
                                        gastos_local2 = copy.copy(gastos_local1)
                                        sondas_local2 = copy.deepcopy(sondas_local1)
                                        f_local2 = copy.copy(f_local1)
                                        max_free_local2 = copy.copy(max_free_local1)
                                        total_free_local2 = copy.copy(total_free_local1)
                                        total_setup_local2 = copy.copy(total_setup_local1)
                                        timer_copy.stop()
                                        
                                        # atualiza tam_prev
                                        tam_prev2 = [v for (v,k) in sondas_local2 if (k==sonda2)][0]
                                        sondas_local2.remove((tam_prev2, sonda2))
                                        heapq.heapify(sondas_local2)
                                        
                                        timer_find.start()
                                        #if (flag_el5 == "janela"):
                                        #    for node6_use in s_local2[sonda2]:
                                        #        if ((release5 == node6_use.data[1]) and (due5 == node6_use.data[2])):
                                        #            break
                                        if (flag_el5 == "projeto"):
                                            for node6_use in s_local2[sonda2]:
                                                if (projeto6 == node6_use.data[0]):
                                                    break
                                        timer_find.stop()
                                        
                                        timer_insere.start()
                                        #if (flag_el5 == "janela"):
                                        #    aloc2, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeJanela(s_local2, node6_use, sonda2, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local2, sondas_local2, f_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev2, debug)
                                        
                                        if (flag_el5 == "projeto"):
                                            aloc2, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeProjeto(s_local2, node6_use, sonda2, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local2, f_local2, sondas_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev2, debug)
                                        timer_insere.stop()
                                        
                                        if (aloc2):
                                            
                                            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data7.pkl'
                                            outfile = open(filename, 'wb')
                                            pickle.dump(s_local2, outfile)
                                            outfile.close()
                                            
                                            # tentar inserir projeto3 na sonda1: enumerar
                                            for el6 in shift_dict[projeto3]:
                                                
                                                if (el6[0] == -1):
                                                    _, sonda5, release6, due6 = el6
                                                    flag_el6 = "janela"
                                                else:
                                                    projeto7, sonda5, _ = el6
                                                    flag_el6 = "projeto"
                                                
                                                if (sonda1 != sonda5):
                                                    continue
                                                
                                                aloc3 = False
                                                
                                                timer_copy.start()
                                                #s_local3 = copy.deepcopy(s_local2)
                                                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data7.pkl'
                                                infile = open(filename, 'rb')
                                                s_local3 = pickle.load(infile)
                                                infile.close()
                                        
                                                gastos_local3 = copy.copy(gastos_local2)
                                                sondas_local3 = copy.deepcopy(sondas_local2)
                                                f_local3 = copy.copy(f_local2)
                                                max_free_local3 = copy.copy(max_free_local2)
                                                total_free_local3 = copy.copy(total_free_local2)
                                                total_setup_local3 = copy.copy(total_setup_local2)
                                                timer_copy.stop()
                                                
                                                tam_prev1 = [v for (v,k) in sondas_local3 if (k==sonda1)][0]
                                                sondas_local3.remove((tam_prev1, sonda1))
                                                heapq.heapify(sondas_local3)
                                                
                                                timer_find.start()
                                                #if (flag_el6 == "janela"):
                                                #    for node7_use in s_local3[sonda1]:
                                                #        if ((release6 == node7_use.data[1]) and (due6 == node7_use.data[2])):
                                                #            break
                                                if (flag_el6 == "projeto"):
                                                    for node7_use in s_local3[sonda1]:
                                                        if (projeto7 == node7_use.data[0]):
                                                            break
                                                timer_find.stop()
                                                
                                                timer_insere.start()
                                                #if (flag_el6 == "janela"):
                                                #    aloc3, gastos_local3, sondas_local3, f_local3, total_free_local3, total_setup_local3, max_free_local3 = TentaInserirNodeDeJanela(s_local3, node7_use, sonda1, projeto3, dados, lag, desloc, proc3, aloc3, gastos_local3, sondas_local3, f_local3, max_free_local3, total_free_local3, total_setup_local3, tam_prev1, debug)
                                                
                                                if (flag_el6 == "projeto"):
                                                    aloc3, gastos_local3, sondas_local3, f_local3, total_free_local3, total_setup_local3, max_free_local3 = TentaInserirNodeDeProjeto(s_local3, node7_use, sonda1, projeto3, dados, lag, desloc, proc3, aloc3, gastos_local3, f_local3, sondas_local3, max_free_local3, total_free_local3, total_setup_local3, tam_prev1, debug)
                                                timer_insere.stop()
                                                
                                                if (aloc3):
                                                    
                                                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data8.pkl'
                                                    outfile = open(filename, 'wb')
                                                    pickle.dump(s_local3, outfile)
                                                    outfile.close()
                                                    
                                                    # tentar inserir projeto4 na sonda1: enumerar
                                                    for el7 in shift_dict[projeto4]:
                                                        
                                                        if (el7[0] == -1):
                                                            _, sonda6, release7, due7 = el7
                                                            flag_el7 = "janela"
                                                        else:
                                                            projeto8, sonda6, _ = el7
                                                            flag_el7 = "projeto"
                                                        
                                                        if (sonda1 != sonda6):
                                                            continue
                                                        
                                                        aloc4 = False
                                                        
                                                        timer_copy.start()
                                                        #s_local4 = copy.deepcopy(s_local3)
                                                        filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data8.pkl'
                                                        infile = open(filename, 'rb')
                                                        s_local4 = pickle.load(infile)
                                                        infile.close()
                                                        
                                                        gastos_local4 = copy.copy(gastos_local3)
                                                        sondas_local4 = copy.deepcopy(sondas_local3)
                                                        f_local4 = copy.copy(f_local3)
                                                        max_free_local4 = copy.copy(max_free_local3)
                                                        total_free_local4 = copy.copy(total_free_local3)
                                                        total_setup_local4 = copy.copy(total_setup_local3)
                                                        timer_copy.stop()
                                                        
                                                        tam_prev1 = [v for (v,k) in sondas_local4 if (k==sonda1)][0]
                                                        sondas_local4.remove((tam_prev1, sonda1))
                                                        heapq.heapify(sondas_local4)
                                                        
                                                        timer_find.start()
                                                        #if (flag_el7 == "janela"):
                                                        #    for node8_use in s_local4[sonda1]:
                                                        #        if ((release7 == node8_use.data[1]) and (due7 == node8_use.data[2])):
                                                        #            break
                                                        if (flag_el7 == "projeto"):
                                                            for node8_use in s_local4[sonda1]:
                                                                if (projeto8 == node8_use.data[0]):
                                                                    break
                                                        timer_find.stop()
                                                        
                                                        timer_insere.start()
                                                        #if (flag_el7 == "janela"):
                                                        #    aloc4, gastos_local4, sondas_local4, f_local4, total_free_local4, total_setup_local4, max_free_local4 = TentaInserirNodeDeJanela(s_local4, node8_use, sonda1, projeto4, dados, lag, desloc, proc4, aloc4, gastos_local4, sondas_local4, f_local4, max_free_local4, total_free_local4, total_setup_local4, tam_prev1, debug)
                                                        
                                                        if (flag_el7 == "projeto"):
                                                            aloc4, gastos_local4, sondas_local4, f_local4, total_free_local4, total_setup_local4, max_free_local4 = TentaInserirNodeDeProjeto(s_local4, node8_use, sonda1, projeto4, dados, lag, desloc, proc4, aloc4, gastos_local4, f_local4, sondas_local4, max_free_local4, total_free_local4, total_setup_local4, tam_prev1, debug)
                                                        timer_insere.stop()
                                                        
                                                        if (aloc4):

                                                            if (total_free_local4 > total_free_best):

                                                                if (debug):
                                                                    print ("Solução vizinha encontrada com melhor total_free")

                                                                s_best = copy.deepcopy(s_local4)
                                                                gastos_best = copy.copy(gastos_local4)
                                                                sondas_best = copy.deepcopy(sondas_local4)
                                                                f_best = copy.copy(f_local4)
                                                                max_free_best = copy.copy(max_free_local4)
                                                                total_free_best = copy.copy(total_free_local4)
                                                                total_setup_best = copy.copy(total_setup_local4)

                                                            elif (total_free_local4 == total_free_best):

                                                                if (-max_free_local4 > -max_free_best):

                                                                    if (debug):
                                                                        print ("Solução vizinha encontrada com melhor max_free")

                                                                    s_best = copy.deepcopy(s_local4)
                                                                    gastos_best = copy.copy(gastos_local4)
                                                                    sondas_best = copy.deepcopy(sondas_local4)
                                                                    f_best = copy.copy(f_local4)
                                                                    max_free_best = copy.copy(max_free_local4)
                                                                    total_free_best = copy.copy(total_free_local4)
                                                                    total_setup_best = copy.copy(total_setup_local4)

                                                                elif (-max_free_local4 == -max_free_best):

                                                                    if (total_setup_local4 < total_setup_best):

                                                                        if (debug):
                                                                            print ("Solução vizinha encontrada com melhor total_setup")

                                                                        s_best = copy.deepcopy(s_local4)
                                                                        gastos_best = copy.copy(gastos_local4)
                                                                        sondas_best = copy.deepcopy(sondas_local4)
                                                                        f_best = copy.copy(f_local4)
                                                                        max_free_best = copy.copy(max_free_local4)
                                                                        total_free_best = copy.copy(total_free_local4)
                                                                        total_setup_best = copy.copy(total_setup_local4)
    
    tempo_total = timer_geral.get_time(reference = "total", unit = "seconds")
    tempo_find = timer_find.get_time(reference = "total", unit = "seconds")
    tempo_remove = timer_remove.get_time(reference = "total", unit = "seconds")
    tempo_insere = timer_insere.get_time(reference = "total", unit = "seconds")
    tempo_copy = timer_copy.get_time(reference = "total", unit = "seconds")
    tempos = tempos = (tempo_preproc, tempo_total, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if (debug):
        print ("Solução final tem:")
        print ("f =", f_best)
        print ("gastos =", gastos_best)
        print ("total_free =", total_free_best)
        print ("max_free =", max_free_best)
        print ("total_setup =", total_setup_best)
        print ("sondas:", sondas)
        print ("Tempo gasto no swap_2x2_interrota: ", tempo_total)
    
    return s_best, gastos_best, sondas_best, f_best, max_free_best, total_free_best, total_setup_best, tempos

def reinsercao_1_intrarota(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, debug=False, k=5):
    
    """
    Documentação: 
    
    Remove projeto de uma sonda e tenta colocar em outro lugar na mesma sonda.
    
    """
    
    if (debug):
        print ("Rodando estrutura de vizinhança: reinsercao(1)")
        print ("Solução inicial tem:")
        print ("f =", f)
        print ("gastos =", gastos)
        print ("total_free =", total_free)
        print ("max_free =", max_free)
        print ("total_setup =", total_setup)
        print ("sondas:", sondas)
    
    import pickle
    import copy
    import heapq
    import CPUtimer
    from time import process_time
    
    s_best = copy.deepcopy(s)
    gastos_best = copy.copy(gastos)
    sondas_best = copy.deepcopy(sondas)
    f_best = copy.copy(f)
    max_free_best = copy.copy(max_free)
    total_free_best = copy.copy(total_free)
    total_setup_best = copy.copy(total_setup)
    
    # gera conjunto de projetos já alocados
    proj_usados = set()
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_usados.add(node.data[0])
    
    # gera conjunto de projetos não alocados
    proj_nao_usados = set()
    for j in range(len(dados[4])):
        if j not in proj_usados:
            if (dados[19][j] > 0):
                proj_nao_usados.add(j)
    
    ans = PreProcessamento(s, desloc, dados, lag, proj_nao_usados, k=k, debug=debug)
    shift_dict, remove_dict, swap_dict, reinsert_dict, insert_fo_dict, swap_1x1_fo_dict, swap_1x2_fo_dict, swap_2x1_fo_dict, swap_2x2_fo_dict, tempo_preproc = ans
    
    timer_geral = CPUtimer.CPUTimer()
    timer_geral.reset()
    timer_geral.start()
    
    timer_find = CPUtimer.CPUTimer()
    timer_find.reset()
    
    timer_insere = CPUtimer.CPUTimer()
    timer_insere.reset()
    
    timer_remove = CPUtimer.CPUTimer()
    timer_remove.reset()
    
    timer_copy = CPUtimer.CPUTimer()
    timer_copy.reset()
    
    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
    outfile = open(filename, 'wb')
    pickle.dump(s, outfile)
    outfile.close()
    
    # enumera todos os projetos que posso tentar remover
    for sonda1 in s.keys():
        for node1 in s[sonda1]:
            
            timer_copy.start()
            #s_removed = copy.deepcopy(s)
            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
            infile = open(filename, 'rb')
            s_removed = pickle.load(infile)
            infile.close()
            
            gastos_removed = copy.copy(gastos)
            sondas_removed = copy.deepcopy(sondas)
            f_removed = copy.copy(f)
            max_free_removed = copy.copy(max_free)
            total_free_removed = copy.copy(total_free)
            total_setup_removed = copy.copy(total_setup)
            timer_copy.stop()
            
            if (node1.data[0] != -1):
                
                timer_find.start()
                for node1_use in s_removed[sonda1]:
                    if (node1.data[0] == node1_use.data[0]):
                        break
                timer_find.stop()
                
                timer_remove.start()
                # tenta remover
                projeto = node1.data[0]
                proc = dados[21][projeto]
                s_removed, flag, node_janela, gastos_removed, sondas_removed, f_removed, max_free_removed, total_free_removed, total_setup_removed = DesalocarProjetoPorNode(s_removed, 
                                                                                projeto, node1_use, sonda1, desloc, 
                                                                                dados, gastos_removed, sondas_removed, f_removed, max_free_removed, 
                                                                                total_free_removed, total_setup_removed, debug)
                timer_remove.stop()
                
                # se não conseguir remover, vai para o próximo node
                if (flag == False):
                    continue
                
                tam_prev = [v for (v,k) in sondas_removed if (k==sonda1)][0]
                sondas_removed.remove((tam_prev, sonda1))
                heapq.heapify(sondas_removed)
                
                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                outfile = open(filename, 'wb')
                pickle.dump(s_removed, outfile)
                outfile.close()
                
                for el in reinsert_dict[projeto]:
                    
                    if (el[0] == -1):
                        _, _, release, due = el
                        flag_el = "janela"
                    else:
                        projeto2, _, _ = el
                        flag_el = "projeto"
                    
                    aloc = False
                    
                    timer_copy.start()
                    #s_local = copy.deepcopy(s_removed)
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                    infile = open(filename, 'rb')
                    s_local = pickle.load(infile)
                    infile.close()
                    
                    gastos_local = copy.copy(gastos_removed)
                    sondas_local = copy.deepcopy(sondas_removed)
                    f_local = copy.copy(f_removed)
                    max_free_local = copy.copy(max_free_removed)
                    total_free_local = copy.copy(total_free_removed)
                    total_setup_local = copy.copy(total_setup_removed)
                    timer_copy.stop()
                    
                    timer_find.start()
                    #if (flag_el == "janela"):
                    #    for node2_use in s_local[sonda1]:
                    #        if ((release == node2_use.data[1]) and (due == node2_use.data[2])):
                    #            break
                    if (flag_el == "projeto"):
                        for node2_use in s_local[sonda1]:
                            if (projeto2 == node2_use.data[0]):
                                break
                    timer_find.stop()
                    
                    timer_insere.start()
                    #if (flag_el == "janela"):
                    #    aloc, gastos_local, sondas_local, f_local, total_free_local, total_setup_local, max_free_local = TentaInserirNodeDeJanela(s_local, node2_use, sonda1, projeto, dados, lag, desloc, proc, aloc, gastos_local, sondas_local, f_local, max_free_local, total_free_local, total_setup_local, tam_prev, debug)
                    
                    if (flag_el == "projeto"):
                        aloc, gastos_local, sondas_local, f_local, total_free_local, total_setup_local, max_free_local = TentaInserirNodeDeProjeto(s_local, node2_use, sonda1, projeto, dados, lag, desloc, proc, aloc, gastos_local, f_local, sondas_local, max_free_local, total_free_local, total_setup_local, tam_prev, debug)
                    timer_insere.stop()
                    
                    if (aloc):
                        
                        if (total_free_local > total_free_best):
                            
                            if (debug):
                                print ("Solução vizinha encontrada com melhor total_free")
                            
                            s_best = copy.deepcopy(s_local)
                            gastos_best = copy.copy(gastos_local)
                            sondas_best = copy.deepcopy(sondas_local)
                            f_best = copy.copy(f_local)
                            max_free_best = copy.copy(max_free_local)
                            total_free_best = copy.copy(total_free_local)
                            total_setup_best = copy.copy(total_setup_local)
                        
                        elif (total_free_local == total_free_best):
                            
                            if (-max_free_local > -max_free_best):
                                
                                if (debug):
                                    print ("Solução vizinha encontrada com melhor max_free")
                                
                                s_best = copy.deepcopy(s_local)
                                gastos_best = copy.copy(gastos_local)
                                sondas_best = copy.deepcopy(sondas_local)
                                f_best = copy.copy(f_local)
                                max_free_best = copy.copy(max_free_local)
                                total_free_best = copy.copy(total_free_local)
                                total_setup_best = copy.copy(total_setup_local)
                            
                            elif (-max_free_local == -max_free_best):
                                
                                if (total_setup_local < total_setup_best):
                                    
                                    if (debug):
                                        print ("Solução vizinha encontrada com melhor total_setup")
                                    
                                    s_best = copy.deepcopy(s_local)
                                    gastos_best = copy.copy(gastos_local)
                                    sondas_best = copy.deepcopy(sondas_local)
                                    f_best = copy.copy(f_local)
                                    max_free_best = copy.copy(max_free_local)
                                    total_free_best = copy.copy(total_free_local)
                                    total_setup_best = copy.copy(total_setup_local)
    
    tempo_total = timer_geral.get_time(reference = "total", unit = "seconds")
    tempo_find = timer_find.get_time(reference = "total", unit = "seconds")
    tempo_insere = timer_insere.get_time(reference = "total", unit = "seconds")
    tempo_remove = timer_remove.get_time(reference = "total", unit = "seconds")
    tempo_copy = timer_copy.get_time(reference = "total", unit = "seconds")
    tempos = (tempo_preproc, tempo_total, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if (debug):
        print ("Solução final tem:")
        print ("f =", f_best)
        print ("gastos =", gastos_best)
        print ("total_free =", total_free_best)
        print ("max_free =", max_free_best)
        print ("total_setup =", total_setup_best)
        print ("sondas:", sondas)
        print ("Tempo gasto na reinsercao_1_intrarota: ", tempo_total)
    
    return s_best, gastos_best, sondas_best, f_best, max_free_best, total_free_best, total_setup_best, tempos

def reinsercao_2_intrarota(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, debug=False, k=5):
    
    """
    Documentação: 
    
    Remove 2 projetos de uma sonda e tenta colocar em outro lugar na mesma sonda.
    
    """
    
    if (debug):
        print ("Rodando estrutura de vizinhança: reinsercao(2)")
        print ("Solução inicial tem:")
        print ("f =", f)
        print ("gastos =", gastos)
        print ("total_free =", total_free)
        print ("max_free =", max_free)
        print ("total_setup =", total_setup)
        print ("sondas:", sondas)
    
    import pickle
    import copy
    import heapq
    import CPUtimer
    from time import process_time
    
    s_best = copy.deepcopy(s)
    gastos_best = copy.copy(gastos)
    sondas_best = copy.deepcopy(sondas)
    f_best = copy.copy(f)
    max_free_best = copy.copy(max_free)
    total_free_best = copy.copy(total_free)
    total_setup_best = copy.copy(total_setup)
    
    # gera conjunto de projetos já alocados
    proj_usados = set()
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_usados.add(node.data[0])
    
    # gera conjunto de projetos não alocados
    proj_nao_usados = set()
    for j in range(len(dados[4])):
        if j not in proj_usados:
            if (dados[19][j] > 0):
                proj_nao_usados.add(j)
    
    ans = PreProcessamento(s, desloc, dados, lag, proj_nao_usados, k=k, debug=debug)
    shift_dict, remove_dict, swap_dict, reinsert_dict, insert_fo_dict, swap_1x1_fo_dict, swap_1x2_fo_dict, swap_2x1_fo_dict, swap_2x2_fo_dict, tempo_preproc = ans
    
    timer_geral = CPUtimer.CPUTimer()
    timer_geral.reset()
    timer_geral.start()
    
    timer_find = CPUtimer.CPUTimer()
    timer_find.reset()
    
    timer_insere = CPUtimer.CPUTimer()
    timer_insere.reset()
    
    timer_remove = CPUtimer.CPUTimer()
    timer_remove.reset()
    
    timer_copy = CPUtimer.CPUTimer()
    timer_copy.reset()
    
    # otimização 1
    pular1 = set()
    
    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
    outfile = open(filename, 'wb')
    pickle.dump(s, outfile)
    outfile.close()
    
    # enumera todos os projetos que posso tentar remover
    for sonda1 in s.keys():
        for node1 in s[sonda1]:
            
            timer_copy.start()
            #s_removed1 = copy.deepcopy(s)
            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
            infile = open(filename, 'rb')
            s_removed1 = pickle.load(infile)
            infile.close()
            
            gastos_removed1 = copy.copy(gastos)
            sondas_removed1 = copy.deepcopy(sondas)
            f_removed1 = copy.copy(f)
            max_free_removed1 = copy.copy(max_free)
            total_free_removed1 = copy.copy(total_free)
            total_setup_removed1 = copy.copy(total_setup)
            timer_copy.stop()
            
            if (node1.data[0] != -1):
                
                timer_find.start()
                for node1_use in s_removed1[sonda1]:
                    if (node1.data[0] == node1_use.data[0]):
                        break
                timer_find.stop()
                
                timer_remove.start()
                # tenta remover
                projeto1 = node1_use.data[0]
                proc1 = dados[21][projeto1]
                
                s_removed1, flag1, node_janela, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, total_free_removed1, total_setup_removed1 = DesalocarProjetoPorNode(s_removed1, 
                                                                                projeto1, node1_use, sonda1, desloc, 
                                                                                dados, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, 
                                                                                total_free_removed1, total_setup_removed1, debug)
                timer_remove.stop()
                
                # se não conseguir remover, vai para o próximo node
                if (flag1 == False):
                    continue
                
                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                outfile = open(filename, 'wb')
                pickle.dump(s_removed1, outfile)
                outfile.close()
                
                for el1 in remove_dict[projeto1]:
                    
                    projeto2, _, _ = el1
                    
                    timer_copy.start()
                    #s_removed2 = copy.deepcopy(s_removed1)
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                    infile = open(filename, 'rb')
                    s_removed2 = pickle.load(infile)
                    infile.close()
                    
                    gastos_removed2 = copy.copy(gastos_removed1)
                    sondas_removed2 = copy.deepcopy(sondas_removed1)
                    f_removed2 = copy.copy(f_removed1)
                    max_free_removed2 = copy.copy(max_free_removed1)
                    total_free_removed2 = copy.copy(total_free_removed1)
                    total_setup_removed2 = copy.copy(total_setup_removed1)
                    timer_copy.stop()
                    
                    timer_find.start()
                    for node3_use in s_removed2[sonda1]:
                        if (projeto2 == node3_use.data[0]):
                            break
                    timer_find.stop()
                    
                    # tenta remover
                    proc2 = dados[21][projeto2]
                    
                    # otimização 1
                    if ( tuple(sorted((projeto1, projeto2))) in pular1 ):
                        continue
                    else:
                        pular1.add(tuple(sorted((projeto1, projeto2))))
                    
                    timer_remove.start()
                    s_removed2, flag2, node_janela, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, total_free_removed2, total_setup_removed2 = DesalocarProjetoPorNode(s_removed2, 
                                                                                    projeto2, node3_use, sonda1, desloc, 
                                                                                    dados, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, 
                                                                                    total_free_removed2, total_setup_removed2, debug)
                    timer_remove.stop()
                    
                    # se não conseguir remover, vai para o próximo node
                    if (flag2 == False):
                        continue
                    
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                    outfile = open(filename, 'wb')
                    pickle.dump(s_removed2, outfile)
                    outfile.close()
                    
                    for el2 in reinsert_dict[projeto1]:
                        
                        if (el2[0] == -1):
                            _, _, release2, due2 = el2
                            flag_el2 = "janela"
                        else:
                            projeto3, _, _ = el2
                            flag_el2 = "projeto"
                        
                        aloc1 = False
                        
                        timer_copy.start()
                        #s_local1 = copy.deepcopy(s_removed2)
                        filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                        infile = open(filename, 'rb')
                        s_local1 = pickle.load(infile)
                        infile.close()
                        
                        gastos_local1 = copy.copy(gastos_removed2)
                        sondas_local1 = copy.deepcopy(sondas_removed2)
                        f_local1 = copy.copy(f_removed2)
                        max_free_local1 = copy.copy(max_free_removed2)
                        total_free_local1 = copy.copy(total_free_removed2)
                        total_setup_local1 = copy.copy(total_setup_removed2)
                        timer_copy.stop()
                        
                        tam_prev = [v for (v,k) in sondas_local1 if (k==sonda1)][0]
                        sondas_local1.remove((tam_prev, sonda1))
                        heapq.heapify(sondas_local1)
                        
                        timer_find.start()
                        #if (flag_el2 == "janela"):
                        #    for node2_use in s_local1[sonda1]:
                        #        if ((release2 == node2_use.data[1]) and (due2 == node2_use.data[2])):
                        #            break
                        if (flag_el2 == "projeto"):
                            for node2_use in s_local1[sonda1]:
                                if (projeto3 == node2_use.data[0]):
                                    break
                        timer_find.stop()
                        
                        timer_insere.start()
                        #if (flag_el2 == "janela"):
                        #    aloc1, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeJanela(s_local1, node2_use, sonda1, projeto1, dados, lag, desloc, proc1, aloc1, gastos_local1, sondas_local1, f_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev, debug)
                        
                        if (flag_el2 == "projeto"):
                            aloc1, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeProjeto(s_local1, node2_use, sonda1, projeto1, dados, lag, desloc, proc1, aloc1, gastos_local1, f_local1, sondas_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev, debug)
                        timer_insere.stop()
                        
                        if (aloc1):
                            
                            tam_prev = [v for (v,k) in sondas_local1 if (k==sonda1)][0]
                            sondas_local1.remove((tam_prev, sonda1))
                            heapq.heapify(sondas_local1)
                            
                            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data4.pkl'
                            outfile = open(filename, 'wb')
                            pickle.dump(s_local1, outfile)
                            outfile.close()
                            
                            for el3 in reinsert_dict[projeto2]:
                                
                                if (el3[0] == -1):
                                    _, _, release3, due3 = el3
                                    flag_el3 = "janela"
                                else:
                                    projeto4, _, _ = el3
                                    flag_el3 = "projeto"
                                
                                aloc2 = False
                                
                                timer_copy.start()
                                #s_local2 = copy.deepcopy(s_local1)
                                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data4.pkl'
                                infile = open(filename, 'rb')
                                s_local2 = pickle.load(infile)
                                infile.close()
                                
                                gastos_local2 = copy.copy(gastos_local1)
                                sondas_local2 = copy.deepcopy(sondas_local1)
                                f_local2 = copy.copy(f_local1)
                                max_free_local2 = copy.copy(max_free_local1)
                                total_free_local2 = copy.copy(total_free_local1)
                                total_setup_local2 = copy.copy(total_setup_local1)
                                timer_copy.stop()
                                
                                timer_find.start()
                                #if (flag_el3 == "janela"):
                                #    for node4_use in s_local2[sonda1]:
                                #        if ((release3 == node4_use.data[1]) and (due3 == node4_use.data[2])):
                                #            break
                                if (flag_el3 == "projeto"):
                                    for node4_use in s_local2[sonda1]:
                                        if (projeto4 == node4_use.data[0]):
                                            break
                                timer_find.stop()
                                
                                timer_insere.start()
                                #if (flag_el3 == "janela"):
                                #    aloc2, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeJanela(s_local2, node4_use, sonda1, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local2, sondas_local2, f_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev, debug)
                                
                                if (flag_el3 == "projeto"):
                                    aloc2, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeProjeto(s_local2, node4_use, sonda1, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local2, f_local2, sondas_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev, debug)
                                timer_insere.stop()
                                
                                if (aloc2):

                                    if (total_free_local2 > total_free_best):

                                        if (debug):
                                            print ("Solução vizinha encontrada com melhor total_free")
                                            print ("sondas = ", sondas)

                                        s_best = copy.deepcopy(s_local2)
                                        gastos_best = copy.copy(gastos_local2)
                                        sondas_best = copy.deepcopy(sondas_local2)
                                        f_best = copy.copy(f_local2)
                                        max_free_best = copy.copy(max_free_local2)
                                        total_free_best = copy.copy(total_free_local2)
                                        total_setup_best = copy.copy(total_setup_local2)

                                    elif (total_free_local2 == total_free_best):

                                        if (-max_free_local2 > -max_free_best):

                                            if (debug):
                                                print ("Solução vizinha encontrada com melhor max_free")
                                                print ("sondas = ", sondas)

                                            s_best = copy.deepcopy(s_local2)
                                            gastos_best = copy.copy(gastos_local2)
                                            sondas_best = copy.deepcopy(sondas_local2)
                                            f_best = copy.copy(f_local2)
                                            max_free_best = copy.copy(max_free_local2)
                                            total_free_best = copy.copy(total_free_local2)
                                            total_setup_best = copy.copy(total_setup_local2)

                                        elif (-max_free_local2 == -max_free_best):

                                            if (total_setup_local2 < total_setup_best):

                                                if (debug):
                                                    print ("Solução vizinha encontrada com melhor total_setup")
                                                    print ("sondas = ", sondas)

                                                s_best = copy.deepcopy(s_local2)
                                                gastos_best = copy.copy(gastos_local2)
                                                sondas_best = copy.deepcopy(sondas_local2)
                                                f_best = copy.copy(f_local2)
                                                max_free_best = copy.copy(max_free_local2)
                                                total_free_best = copy.copy(total_free_local2)
                                                total_setup_best = copy.copy(total_setup_local2)
    
    tempo_total = timer_geral.get_time(reference = "total", unit = "seconds")
    tempo_find = timer_find.get_time(reference = "total", unit = "seconds")
    tempo_insere = timer_insere.get_time(reference = "total", unit = "seconds")
    tempo_remove = timer_remove.get_time(reference = "total", unit = "seconds")
    tempo_copy = timer_copy.get_time(reference = "total", unit = "seconds")
    tempos = (tempo_preproc, tempo_total, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if (debug):
        print ("Solução final tem:")
        print ("f =", f_best)
        print ("gastos =", gastos_best)
        print ("total_free =", total_free_best)
        print ("max_free =", max_free_best)
        print ("total_setup =", total_setup_best)
        print ("sondas:", sondas)
        print ("Tempo gasto na reinsercao_2_intrarota: ", tempo_total)
    
    return s_best, gastos_best, sondas_best, f_best, max_free_best, total_free_best, total_setup_best, tempos

def inserir_novo_fo(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, custo_total, debug=False, k=5):
    
    """
    Documentação: 
    
    Tenta alocar algum projeto ainda não alocado.
    
    """
    
    if (debug):
        print ("Rodando estrutura de vizinhança: inserir_novo()")
        print ("Solução inicial tem:")
        print ("f =", f)
        print ("gastos =", gastos)
        print ("total_free =", total_free)
        print ("max_free =", max_free)
        print ("total_setup =", total_setup)
        print ("sondas:", sondas)
    
    import pickle
    import copy
    import heapq
    import CPUtimer
    from time import process_time
    
    s_best = copy.deepcopy(s)
    gastos_best = copy.copy(gastos)
    sondas_best = copy.deepcopy(sondas)
    f_best = copy.copy(f)
    max_free_best = copy.copy(max_free)
    total_free_best = copy.copy(total_free)
    total_setup_best = copy.copy(total_setup)
    
    # gera conjunto de projetos já alocados
    proj_usados = set()
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_usados.add(node.data[0])
    
    # gera conjunto de projetos não alocados
    proj_nao_usados = set()
    for j in range(len(dados[4])):
        if j not in proj_usados:
            if (dados[19][j] > 0):
                proj_nao_usados.add(j)
    
    ans = PreProcessamento(s, desloc, dados, lag, proj_nao_usados, k=k, debug=debug)
    shift_dict, remove_dict, swap_dict, reinsert_dict, insert_fo_dict, swap_1x1_fo_dict, swap_1x2_fo_dict, swap_2x1_fo_dict, swap_2x2_fo_dict, tempo_preproc = ans
    
    timer_geral = CPUtimer.CPUTimer()
    timer_geral.reset()
    timer_geral.start()
    
    timer_find = CPUtimer.CPUTimer()
    timer_find.reset()
    
    timer_insere = CPUtimer.CPUTimer()
    timer_insere.reset()
    
    timer_remove = CPUtimer.CPUTimer()
    timer_remove.reset()
    
    timer_copy = CPUtimer.CPUTimer()
    timer_copy.reset()
    
    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
    outfile = open(filename, 'wb')
    pickle.dump(s, outfile)
    outfile.close()
    
    # enumera todos os projetos não alocados
    for proj_out in proj_nao_usados:
        
        projeto = proj_out
        proc = dados[21][projeto]
        
        # pular se ultrapassa limite de gastos
        if (gastos + dados[20][projeto] > custo_total):
            continue
        
        # tentar inserir: enumerar
        for el in insert_fo_dict[projeto]:
            
            if (el[0] == -1):
                _, sonda, release, due = el
                flag_el = "janela"
            else:
                projeto2, sonda, _ = el
                flag_el = "projeto"
            
            aloc = False
            
            timer_copy.start()
            #s_local = copy.deepcopy(s)
            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
            infile = open(filename, 'rb')
            s_local = pickle.load(infile)
            infile.close()
            
            gastos_local = copy.copy(gastos)
            sondas_local = copy.deepcopy(sondas)
            f_local = copy.copy(f)
            max_free_local = copy.copy(max_free)
            total_free_local = copy.copy(total_free)
            total_setup_local = copy.copy(total_setup)
            timer_copy.stop()
            
            tam_prev = [v for (v,k) in sondas_local if (k==sonda)][0]
            sondas_local.remove((tam_prev, sonda))
            heapq.heapify(sondas_local)
            
            timer_find.start()
            #if (flag_el == "janela"):
            #    for node_use in s_local[sonda]:
            #        if ((release == node_use.data[1]) and (due == node_use.data[2])):
            #            break
            if (flag_el == "projeto"):
                for node_use in s_local[sonda]:
                    if (projeto2 == node_use.data[0]):
                        break
            timer_find.stop()
            
            timer_insere.start()
            #if (flag_el == "janela"):
            #    aloc, gastos_local, sondas_local, f_local, total_free_local, total_setup_local, max_free_local = TentaInserirNodeDeJanela(s_local, node_use, sonda, projeto, dados, lag, desloc, proc, aloc, gastos_local, sondas_local, f_local, max_free_local, total_free_local, total_setup_local, tam_prev, debug)
            
            if (flag_el == "projeto"):
                aloc, gastos_local, sondas_local, f_local, total_free_local, total_setup_local, max_free_local = TentaInserirNodeDeProjeto(s_local, node_use, sonda, projeto, dados, lag, desloc, proc, aloc, gastos_local, f_local, sondas_local, max_free_local, total_free_local, total_setup_local, tam_prev, debug)
            timer_insere.stop()
            
            if (aloc):

                if (f_local > f_best):

                    if (debug):
                        print ("Solução vizinha encontrada com melhor fitness")

                    s_best = copy.deepcopy(s_local)
                    gastos_best = copy.copy(gastos_local)
                    sondas_best = copy.deepcopy(sondas_local)
                    f_best = copy.copy(f_local)
                    max_free_best = copy.copy(max_free_local)
                    total_free_best = copy.copy(total_free_local)
                    total_setup_best = copy.copy(total_setup_local)

                elif (f_local == f_best):

                    if (total_free_local > total_free_best):

                        if (debug):
                            print ("Solução vizinha encontrada com melhor total_free")

                        s_best = copy.deepcopy(s_local)
                        gastos_best = copy.copy(gastos_local)
                        sondas_best = copy.deepcopy(sondas_local)
                        f_best = copy.copy(f_local)
                        max_free_best = copy.copy(max_free_local)
                        total_free_best = copy.copy(total_free_local)
                        total_setup_best = copy.copy(total_setup_local)

                    elif (total_free_local == total_free_best):

                        if (-max_free_local > -max_free_best):

                            if (debug):
                                print ("Solução vizinha encontrada com melhor max_free")

                            s_best = copy.deepcopy(s_local)
                            gastos_best = copy.copy(gastos_local)
                            sondas_best = copy.deepcopy(sondas_local)
                            f_best = copy.copy(f_local)
                            max_free_best = copy.copy(max_free_local)
                            total_free_best = copy.copy(total_free_local)
                            total_setup_best = copy.copy(total_setup_local)

                        elif (-max_free_local == -max_free_best):

                            if (total_setup_local < total_setup_best):

                                if (debug):
                                    print ("Solução vizinha encontrada com melhor total_setup")

                                s_best = copy.deepcopy(s_local)
                                gastos_best = copy.copy(gastos_local)
                                sondas_best = copy.deepcopy(sondas_local)
                                f_best = copy.copy(f_local)
                                max_free_best = copy.copy(max_free_local)
                                total_free_best = copy.copy(total_free_local)
                                total_setup_best = copy.copy(total_setup_local)
    
    tempo_total = timer_geral.get_time(reference = "total", unit = "seconds")
    tempo_find = timer_find.get_time(reference = "total", unit = "seconds")
    tempo_insere = timer_insere.get_time(reference = "total", unit = "seconds")
    tempo_remove = timer_remove.get_time(reference = "total", unit = "seconds")
    tempo_copy = timer_copy.get_time(reference = "total", unit = "seconds")
    tempos = (tempo_preproc, tempo_total, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if (debug):
        print ("Solução final tem:")
        print ("f =", f_best)
        print ("gastos =", gastos_best)
        print ("total_free =", total_free_best)
        print ("max_free =", max_free_best)
        print ("total_setup =", total_setup_best)
        print ("sondas:", sondas)
        print ("Tempo gasto em inserir_novo_fo: ", tempo_total)
    
    return s_best, gastos_best, sondas_best, f_best, max_free_best, total_free_best, total_setup_best, tempos

def swap_1x1_fo(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, custo_total, debug=False, k=5):
    
    """
    Documentação: 
    
    Tenta trocar um projeto alocado com um não alocado.
    
    """
    
    if (debug):
        print ("Rodando estrutura de vizinhança: swapFO(1, 1)")
        print ("Solução inicial tem:")
        print ("f =", f)
        print ("gastos =", gastos)
        print ("total_free =", total_free)
        print ("max_free =", max_free)
        print ("total_setup =", total_setup)
        print ("sondas:", sondas)
    
    import pickle
    import copy
    import heapq
    import CPUtimer
    from time import process_time
    
    s_best = copy.deepcopy(s)
    gastos_best = copy.copy(gastos)
    sondas_best = copy.deepcopy(sondas)
    f_best = copy.copy(f)
    max_free_best = copy.copy(max_free)
    total_free_best = copy.copy(total_free)
    total_setup_best = copy.copy(total_setup)
    
    # gera conjunto de projetos já alocados
    proj_usados = set()
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_usados.add(node.data[0])
    
    # gera conjunto de projetos não alocados
    proj_nao_usados = set()
    for j in range(len(dados[4])):
        if j not in proj_usados:
            if (dados[19][j] > 0):
                proj_nao_usados.add(j)
    
    ans = PreProcessamento(s, desloc, dados, lag, proj_nao_usados, k=k, debug=debug)
    shift_dict, remove_dict, swap_dict, reinsert_dict, insert_fo_dict, swap_1x1_fo_dict, swap_1x2_fo_dict, swap_2x1_fo_dict, swap_2x2_fo_dict, tempo_preproc = ans
    
    timer_geral = CPUtimer.CPUTimer()
    timer_geral.reset()
    timer_geral.start()
    
    timer_find = CPUtimer.CPUTimer()
    timer_find.reset()
    
    timer_insere = CPUtimer.CPUTimer()
    timer_insere.reset()
    
    timer_remove = CPUtimer.CPUTimer()
    timer_remove.reset()
    
    timer_copy = CPUtimer.CPUTimer()
    timer_copy.reset()
    
    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
    outfile = open(filename, 'wb')
    pickle.dump(s, outfile)
    outfile.close()
    
    # enumera todos os projetos que posso tentar remover
    for sonda in s.keys():
        for node1 in s[sonda]:
            
            timer_copy.start()
            #s_removed = copy.deepcopy(s)
            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
            infile = open(filename, 'rb')
            s_removed = pickle.load(infile)
            infile.close()
            
            gastos_removed = copy.copy(gastos)
            sondas_removed = copy.deepcopy(sondas)
            f_removed = copy.copy(f)
            max_free_removed = copy.copy(max_free)
            total_free_removed = copy.copy(total_free)
            total_setup_removed = copy.copy(total_setup)
            timer_copy.stop()
            
            if (node1.data[0] != -1):
                
                timer_find.start()
                for node1_use in s_removed[sonda]:
                    if (node1.data[0] == node1_use.data[0]):
                        break
                timer_find.stop()
                
                timer_remove.start()
                # tenta remover
                projeto1 = node1.data[0]
                proc1 = dados[21][projeto1]
                s_removed, flag, node_janela, gastos_removed, sondas_removed, f_removed, max_free_removed, total_free_removed, total_setup_removed = DesalocarProjetoPorNode(s_removed, 
                                                                                projeto1, node1_use, sonda, desloc, 
                                                                                dados, gastos_removed, sondas_removed, f_removed, max_free_removed, 
                                                                                total_free_removed, total_setup_removed, debug)
                timer_remove.stop()
                
                # se não conseguir remover, vai para o próximo node
                if (flag == False):
                    continue
                
                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                outfile = open(filename, 'wb')
                pickle.dump(s_removed, outfile)
                outfile.close()
                
                # enumerar projetos não alocados
                for el1 in swap_1x1_fo_dict[projeto1]:
                    
                    projeto2, _, _ = el1
                    
                    proc2 = dados[21][projeto2]
                    
                    # pular se ultrapassa limite de gastos
                    if (gastos_removed + dados[20][projeto2] > custo_total):
                        continue
                    
                    # tentar inserir na sonda do projeto que foi removido
                    for el2 in insert_fo_dict[projeto2]:
                        
                        if (el2[0] == -1):
                            _, sonda2, release2, due2 = el2
                            flag_el2 = "janela"
                        else:
                            projeto3, sonda2, _ = el2
                            flag_el2 = "projeto"
                        
                        if (sonda2 != sonda):
                            continue
                        
                        aloc2 = False
                        
                        timer_copy.start()
                        #s_local = copy.deepcopy(s_removed)
                        filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                        infile = open(filename, 'rb')
                        s_local = pickle.load(infile)
                        infile.close()
                        
                        gastos_local = copy.copy(gastos_removed)
                        sondas_local = copy.deepcopy(sondas_removed)
                        f_local = copy.copy(f_removed)
                        max_free_local = copy.copy(max_free_removed)
                        total_free_local = copy.copy(total_free_removed)
                        total_setup_local = copy.copy(total_setup_removed)
                        timer_copy.stop()
                        
                        tam_prev = [v for (v,k) in sondas_local if (k==sonda)][0]
                        sondas_local.remove((tam_prev, sonda))
                        heapq.heapify(sondas_local)
                        
                        timer_find.start()
                        #if (flag_el2 == "janela"):
                        #    for node2_use in s_local[sonda]:
                        #        if ((release2 == node2_use.data[1]) and (due2 == node2_use.data[2])):
                        #            break
                        if (flag_el2 == "projeto"):
                            for node2_use in s_local[sonda]:
                                if (projeto3 == node2_use.data[0]):
                                    break
                        timer_find.stop()
                        
                        timer_insere.start()
                        #if (flag_el2 == "janela"):
                        #    aloc2, gastos_local, sondas_local, f_local, total_free_local, total_setup_local, max_free_local = TentaInserirNodeDeJanela(s_local, node2_use, sonda, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local, sondas_local, f_local, max_free_local, total_free_local, total_setup_local, tam_prev, debug)
                        
                        if (flag_el2 == "projeto"):
                            aloc2, gastos_local, sondas_local, f_local, total_free_local, total_setup_local, max_free_local = TentaInserirNodeDeProjeto(s_local, node2_use, sonda, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local, f_local, sondas_local, max_free_local, total_free_local, total_setup_local, tam_prev, debug)
                        timer_insere.stop()
                        
                        if (aloc2):
                            
                            if (f_local > f_best):
                                
                                if (debug):
                                    print ("Solução vizinha encontrada com melhor fitness")
                                
                                s_best = copy.deepcopy(s_local)
                                gastos_best = copy.copy(gastos_local)
                                sondas_best = copy.deepcopy(sondas_local)
                                f_best = copy.copy(f_local)
                                max_free_best = copy.copy(max_free_local)
                                total_free_best = copy.copy(total_free_local)
                                total_setup_best = copy.copy(total_setup_local)
                            
                            elif (f_local == f_best):
                                
                                if (gastos_local < gastos_best):
                                    
                                    if (debug):
                                        print ("Solução vizinha encontrada com melhor gastos")
                                    
                                    s_best = copy.deepcopy(s_local)
                                    gastos_best = copy.copy(gastos_local)
                                    sondas_best = copy.deepcopy(sondas_local)
                                    f_best = copy.copy(f_local)
                                    max_free_best = copy.copy(max_free_local)
                                    total_free_best = copy.copy(total_free_local)
                                    total_setup_best = copy.copy(total_setup_local)
                                
                                elif (gastos_local == gastos_best):
                                    
                                    if (total_free_local > total_free_best):
                                        
                                        if (debug):
                                            print ("Solução vizinha encontrada com melhor total_free")
                                        
                                        s_best = copy.deepcopy(s_local)
                                        gastos_best = copy.copy(gastos_local)
                                        sondas_best = copy.deepcopy(sondas_local)
                                        f_best = copy.copy(f_local)
                                        max_free_best = copy.copy(max_free_local)
                                        total_free_best = copy.copy(total_free_local)
                                        total_setup_best = copy.copy(total_setup_local)
                                    
                                    elif (total_free_local == total_free_best):
                                        
                                        if (-max_free_local > -max_free_best):
                                            
                                            if (debug):
                                                print ("Solução vizinha encontrada com melhor max_free")
                                            
                                            s_best = copy.deepcopy(s_local)
                                            gastos_best = copy.copy(gastos_local)
                                            sondas_best = copy.deepcopy(sondas_local)
                                            f_best = copy.copy(f_local)
                                            max_free_best = copy.copy(max_free_local)
                                            total_free_best = copy.copy(total_free_local)
                                            total_setup_best = copy.copy(total_setup_local)
                                        
                                        elif (-max_free_local == -max_free_best):
                                            
                                            if (total_setup_local < total_setup_best):
                                                
                                                if (debug):
                                                    print ("Solução vizinha encontrada com melhor total_setup")
                                                
                                                s_best = copy.deepcopy(s_local)
                                                gastos_best = copy.copy(gastos_local)
                                                sondas_best = copy.deepcopy(sondas_local)
                                                f_best = copy.copy(f_local)
                                                max_free_best = copy.copy(max_free_local)
                                                total_free_best = copy.copy(total_free_local)
                                                total_setup_best = copy.copy(total_setup_local)
    
    tempo_total = timer_geral.get_time(reference = "total", unit = "seconds")
    tempo_find = timer_find.get_time(reference = "total", unit = "seconds")
    tempo_insere = timer_insere.get_time(reference = "total", unit = "seconds")
    tempo_remove = timer_remove.get_time(reference = "total", unit = "seconds")
    tempo_copy = timer_copy.get_time(reference = "total", unit = "seconds")
    tempos = (tempo_preproc, tempo_total, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if (debug):
        print ("Solução final tem:")
        print ("f =", f_best)
        print ("gastos =", gastos_best)
        print ("total_free =", total_free_best)
        print ("max_free =", max_free_best)
        print ("total_setup =", total_setup_best)
        print ("sondas:", sondas)
        print ("Tempo gasto no swap_1x1_fo: ", tempo_total)
    
    return s_best, gastos_best, sondas_best, f_best, max_free_best, total_free_best, total_setup_best, tempos

def swap_1x2_fo(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, custo_total, debug=False, k=5):
    
    """
    Documentação: 
    
    Tenta trocar um projeto alocado por dois não alocados.
    
    """
    
    if (debug):
        print ("Rodando estrutura de vizinhança: swapFO(1, 2)")
        print ("Solução inicial tem:")
        print ("f =", f)
        print ("gastos =", gastos)
        print ("total_free =", total_free)
        print ("max_free =", max_free)
        print ("total_setup =", total_setup)
        print ("sondas:", sondas)
    
    import pickle
    import copy
    import heapq
    import CPUtimer
    from time import process_time
    
    s_best = copy.deepcopy(s)
    gastos_best = copy.copy(gastos)
    sondas_best = copy.deepcopy(sondas)
    f_best = copy.copy(f)
    max_free_best = copy.copy(max_free)
    total_free_best = copy.copy(total_free)
    total_setup_best = copy.copy(total_setup)
    
    # gera conjunto de projetos já alocados
    proj_usados = set()
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_usados.add(node.data[0])
    
    # gera conjunto de projetos não alocados
    proj_nao_usados = set()
    for j in range(len(dados[4])):
        if j not in proj_usados:
            if (dados[19][j] > 0):
                proj_nao_usados.add(j)
    
    ans = PreProcessamento(s, desloc, dados, lag, proj_nao_usados, k=k, debug=debug)
    shift_dict, remove_dict, swap_dict, reinsert_dict, insert_fo_dict, swap_1x1_fo_dict, swap_1x2_fo_dict, swap_2x1_fo_dict, swap_2x2_fo_dict, tempo_preproc = ans
    
    timer_geral = CPUtimer.CPUTimer()
    timer_geral.reset()
    timer_geral.start()
    
    timer_find = CPUtimer.CPUTimer()
    timer_find.reset()
    
    timer_insere = CPUtimer.CPUTimer()
    timer_insere.reset()
    
    timer_remove = CPUtimer.CPUTimer()
    timer_remove.reset()
    
    timer_copy = CPUtimer.CPUTimer()
    timer_copy.reset()
    
    # otimização1
    pular1 = set()
    
    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
    outfile = open(filename, 'wb')
    pickle.dump(s, outfile)
    outfile.close()
    
    # enumera todos os projetos que posso tentar remover
    for sonda in s.keys():
        for node1 in s[sonda]:
            
            timer_copy.start()
            #s_removed = copy.deepcopy(s)
            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
            infile = open(filename, 'rb')
            s_removed = pickle.load(infile)
            infile.close()
            
            gastos_removed = copy.copy(gastos)
            sondas_removed = copy.deepcopy(sondas)
            f_removed = copy.copy(f)
            max_free_removed = copy.copy(max_free)
            total_free_removed = copy.copy(total_free)
            total_setup_removed = copy.copy(total_setup)
            timer_copy.stop()
            
            if (node1.data[0] != -1):
                
                timer_find.start()
                for node1_use in s_removed[sonda]:
                    if (node1.data[0] == node1_use.data[0]):
                        break
                timer_find.stop()
                
                timer_remove.start()
                # tenta remover
                projeto1 = node1.data[0]
                proc1 = dados[21][projeto1]
                s_removed, flag, node_janela, gastos_removed, sondas_removed, f_removed, max_free_removed, total_free_removed, total_setup_removed = DesalocarProjetoPorNode(s_removed, 
                                                                                projeto1, node1_use, sonda, desloc, 
                                                                                dados, gastos_removed, sondas_removed, f_removed, max_free_removed, 
                                                                                total_free_removed, total_setup_removed, debug)
                timer_remove.stop()
                
                # se não conseguir remover, vai para o próximo node
                if (flag == False):
                    continue
                
                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                outfile = open(filename, 'wb')
                pickle.dump(s_removed, outfile)
                outfile.close()
                
                # enumerar projetos não alocados
                for el1 in swap_1x2_fo_dict[projeto1]:
                    
                    projeto2, _, _ = el1
                    
                    proc2 = dados[21][projeto2]
                    
                    # pular se ultrapassa limite de gastos
                    if (gastos_removed + dados[20][projeto2] > custo_total):
                        continue
                    
                    # tentar inserir na sonda do projeto que foi removido
                    for el2 in insert_fo_dict[projeto2]:
                        
                        if (el2[0] == -1):
                            _, sonda2, release2, due2 = el2
                            flag_el2 = "janela"
                        else:
                            projeto4, sonda2, _ = el2
                            flag_el2 = "projeto"
                        
                        if (sonda2 != sonda):
                            continue
                        
                        aloc2 = False
                        
                        timer_copy.start()
                        #s_local1 = copy.deepcopy(s_removed)
                        filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                        infile = open(filename, 'rb')
                        s_local1 = pickle.load(infile)
                        infile.close()
                        
                        gastos_local1 = copy.copy(gastos_removed)
                        sondas_local1 = copy.deepcopy(sondas_removed)
                        f_local1 = copy.copy(f_removed)
                        max_free_local1 = copy.copy(max_free_removed)
                        total_free_local1 = copy.copy(total_free_removed)
                        total_setup_local1 = copy.copy(total_setup_removed)
                        timer_copy.stop()
                        
                        tam_prev = [v for (v,k) in sondas_local1 if (k==sonda)][0]
                        sondas_local1.remove((tam_prev, sonda))
                        heapq.heapify(sondas_local1)
                        
                        timer_find.start()
                        #if (flag_el2 == "janela"):
                        #    for node2_use in s_local1[sonda]:
                        #        if ((release2 == node2_use.data[1]) and (due2 == node2_use.data[2])):
                        #            break
                        if (flag_el2 == "projeto"):
                            for node2_use in s_local1[sonda]:
                                if (projeto4 == node2_use.data[0]):
                                    break
                        timer_find.stop()
                        
                        timer_insere.start()
                        #if (flag_el2 == "janela"):
                        #    aloc2, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeJanela(s_local1, node2_use, sonda, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local1, sondas_local1, f_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev, debug)
                        
                        if (flag_el2 == "projeto"):
                            aloc2, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeProjeto(s_local1, node2_use, sonda, projeto2, dados, lag, desloc, proc2, aloc2, gastos_local1, f_local1, sondas_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev, debug)
                        timer_insere.stop()
                        
                        if (aloc2):
                            
                            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                            outfile = open(filename, 'wb')
                            pickle.dump(s_local1, outfile)
                            outfile.close()
                            
                            for el3 in swap_1x2_fo_dict[projeto1]:
                                
                                projeto3, _, _ = el3
                                
                                if (projeto3 == projeto2):
                                    continue
                                
                                proc3 = dados[21][projeto3]
                                
                                # otimização 1
                                if ( tuple(sorted((projeto2, projeto3))) in pular1 ):
                                    continue
                                else:
                                    pular1.add(tuple(sorted((projeto2, projeto3))))
                                
                                # pular se ultrapassa limite de gastos
                                if (gastos_local1 + dados[20][projeto3] > custo_total):
                                    continue
                                
                                # tentar inserir na sonda do projeto que foi removido
                                for el4 in insert_fo_dict[projeto3]:
                                    
                                    if (el4[0] == -1):
                                        _, sonda3, release4, due4 = el4
                                        flag_el4 = "janela"
                                    else:
                                        projeto5, sonda3, _ = el4
                                        flag_el4 = "projeto"
                                    
                                    if (sonda3 != sonda):
                                        continue
                                    
                                    aloc3 = False
                                    
                                    timer_copy.start()
                                    #s_local2 = copy.deepcopy(s_local1)
                                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                                    infile = open(filename, 'rb')
                                    s_local2 = pickle.load(infile)
                                    infile.close()
                                    
                                    gastos_local2 = copy.copy(gastos_local1)
                                    sondas_local2 = copy.deepcopy(sondas_local1)
                                    f_local2 = copy.copy(f_local1)
                                    max_free_local2 = copy.copy(max_free_local1)
                                    total_free_local2 = copy.copy(total_free_local1)
                                    total_setup_local2 = copy.copy(total_setup_local1)
                                    timer_copy.stop()
                                    
                                    tam_prev = [v for (v,k) in sondas_local2 if (k==sonda)][0]
                                    sondas_local2.remove((tam_prev, sonda))
                                    heapq.heapify(sondas_local2)
                                    
                                    timer_find.start()
                                    #if (flag_el4 == "janela"):
                                    #    for node3_use in s_local2[sonda]:
                                    #        if ((release4 == node3_use.data[1]) and (due4 == node3_use.data[2])):
                                    #            break
                                    if (flag_el4 == "projeto"):
                                        for node3_use in s_local2[sonda]:
                                            if (projeto5 == node3_use.data[0]):
                                                break
                                    timer_find.stop()
                                    
                                    timer_insere.start()
                                    #if (flag_el4 == "janela"):
                                    #    aloc3, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeJanela(s_local2, node3_use, sonda, projeto3, dados, lag, desloc, proc3, aloc3, gastos_local2, sondas_local2, f_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev, debug)
                                    
                                    if (flag_el4 == "projeto"):
                                        aloc3, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeProjeto(s_local2, node3_use, sonda, projeto3, dados, lag, desloc, proc3, aloc3, gastos_local2, f_local2, sondas_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev, debug)
                                    timer_insere.stop()
                                    
                                    if (aloc3):
                                        
                                        if (f_local2 > f_best):
                                            
                                            if (debug):
                                                print ("Solução vizinha encontrada com melhor fitness")
                                            
                                            s_best = copy.deepcopy(s_local2)
                                            gastos_best = copy.copy(gastos_local2)
                                            sondas_best = copy.deepcopy(sondas_local2)
                                            f_best = copy.copy(f_local2)
                                            max_free_best = copy.copy(max_free_local2)
                                            total_free_best = copy.copy(total_free_local2)
                                            total_setup_best = copy.copy(total_setup_local2)
                                        
                                        elif (f_local2 == f_best):
                                            
                                            if (gastos_local2 < gastos_best):
                                                
                                                if (debug):
                                                    print ("Solução vizinha encontrada com melhor gastos")
                                                
                                                s_best = copy.deepcopy(s_local2)
                                                gastos_best = copy.copy(gastos_local2)
                                                sondas_best = copy.deepcopy(sondas_local2)
                                                f_best = copy.copy(f_local2)
                                                max_free_best = copy.copy(max_free_local2)
                                                total_free_best = copy.copy(total_free_local2)
                                                total_setup_best = copy.copy(total_setup_local2)
                                            
                                            elif (gastos_local2 == gastos_best):
                                                
                                                if (total_free_local2 > total_free_best):
                                                    
                                                    if (debug):
                                                        print ("Solução vizinha encontrada com melhor total_free")
                                                    
                                                    s_best = copy.deepcopy(s_local2)
                                                    gastos_best = copy.copy(gastos_local2)
                                                    sondas_best = copy.deepcopy(sondas_local2)
                                                    f_best = copy.copy(f_local2)
                                                    max_free_best = copy.copy(max_free_local2)
                                                    total_free_best = copy.copy(total_free_local2)
                                                    total_setup_best = copy.copy(total_setup_local2)
                                                
                                                elif (total_free_local2 == total_free_best):
                                                    
                                                    if (-max_free_local2 > -max_free_best):
                                                        
                                                        if (debug):
                                                            print ("Solução vizinha encontrada com melhor max_free")
                                                        
                                                        s_best = copy.deepcopy(s_local2)
                                                        gastos_best = copy.copy(gastos_local2)
                                                        sondas_best = copy.deepcopy(sondas_local2)
                                                        f_best = copy.copy(f_local2)
                                                        max_free_best = copy.copy(max_free_local2)
                                                        total_free_best = copy.copy(total_free_local2)
                                                        total_setup_best = copy.copy(total_setup_local2)
                                                    
                                                    elif (-max_free_local2 == -max_free_best):
                                                        
                                                        if (total_setup_local2 < total_setup_best):
                                                            
                                                            if (debug):
                                                                print ("Solução vizinha encontrada com melhor total_setup")
                                                            
                                                            s_best = copy.deepcopy(s_local2)
                                                            gastos_best = copy.copy(gastos_local2)
                                                            sondas_best = copy.deepcopy(sondas_local2)
                                                            f_best = copy.copy(f_local2)
                                                            max_free_best = copy.copy(max_free_local2)
                                                            total_free_best = copy.copy(total_free_local2)
                                                            total_setup_best = copy.copy(total_setup_local2)
    
    tempo_total = timer_geral.get_time(reference = "total", unit = "seconds")
    tempo_find = timer_find.get_time(reference = "total", unit = "seconds")
    tempo_insere = timer_insere.get_time(reference = "total", unit = "seconds")
    tempo_remove = timer_remove.get_time(reference = "total", unit = "seconds")
    tempo_copy = timer_copy.get_time(reference = "total", unit = "seconds")
    tempos = (tempo_preproc, tempo_total, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if (debug):
        print ("Solução final tem:")
        print ("f =", f_best)
        print ("gastos =", gastos_best)
        print ("total_free =", total_free_best)
        print ("max_free =", max_free_best)
        print ("total_setup =", total_setup_best)
        print ("sondas:", sondas)
        print ("Tempo gasto no swap_1x2_fo: ", tempo_total)
    
    return s_best, gastos_best, sondas_best, f_best, max_free_best, total_free_best, total_setup_best, tempos

def swap_2x1_fo(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, custo_total, debug=False, k=5):
    
    """
    Documentação: 
    
    Tenta trocar dois projetos alocados com um não alocado.
    
    """
    
    if (debug):
        print ("Rodando estrutura de vizinhança: swapFO(2, 1)")
        print ("Solução inicial tem:")
        print ("f =", f)
        print ("gastos =", gastos)
        print ("total_free =", total_free)
        print ("max_free =", max_free)
        print ("total_setup =", total_setup)
        print ("sondas:", sondas)
    
    import pickle
    import copy
    import heapq
    import CPUtimer
    from time import process_time
    
    s_best = copy.deepcopy(s)
    gastos_best = copy.copy(gastos)
    sondas_best = copy.deepcopy(sondas)
    f_best = copy.copy(f)
    max_free_best = copy.copy(max_free)
    total_free_best = copy.copy(total_free)
    total_setup_best = copy.copy(total_setup)
    
    # gera conjunto de projetos já alocados
    proj_usados = set()
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_usados.add(node.data[0])
    
    # gera conjunto de projetos não alocados
    proj_nao_usados = set()
    for j in range(len(dados[4])):
        if j not in proj_usados:
            if (dados[19][j] > 0):
                proj_nao_usados.add(j)
    
    ans = PreProcessamento(s, desloc, dados, lag, proj_nao_usados, k=k, debug=debug)
    shift_dict, remove_dict, swap_dict, reinsert_dict, insert_fo_dict, swap_1x1_fo_dict, swap_1x2_fo_dict, swap_2x1_fo_dict, swap_2x2_fo_dict, tempo_preproc = ans
    
    timer_geral = CPUtimer.CPUTimer()
    timer_geral.reset()
    timer_geral.start()
    
    timer_find = CPUtimer.CPUTimer()
    timer_find.reset()
    
    timer_insere = CPUtimer.CPUTimer()
    timer_insere.reset()
    
    timer_remove = CPUtimer.CPUTimer()
    timer_remove.reset()
    
    timer_copy = CPUtimer.CPUTimer()
    timer_copy.reset()
    
    # otimização 1
    pular1 = set()
    
    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
    outfile = open(filename, 'wb')
    pickle.dump(s, outfile)
    outfile.close()
    
    # enumera todos os projetos que posso tentar remover
    for sonda in s.keys():
        for node1 in s[sonda]:
            
            timer_copy.start()
            #s_removed1 = copy.deepcopy(s)
            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
            infile = open(filename, 'rb')
            s_removed1 = pickle.load(infile)
            infile.close()
            
            gastos_removed1 = copy.copy(gastos)
            sondas_removed1 = copy.deepcopy(sondas)
            f_removed1 = copy.copy(f)
            max_free_removed1 = copy.copy(max_free)
            total_free_removed1 = copy.copy(total_free)
            total_setup_removed1 = copy.copy(total_setup)
            timer_copy.stop()
            
            if (node1.data[0] != -1):
                
                timer_find.start()
                for node1_use in s_removed1[sonda]:
                    if (node1.data[0] == node1_use.data[0]):
                        break
                timer_find.stop()
                
                timer_remove.start()
                # tenta remover
                projeto1 = node1.data[0]
                
                s_removed1, flag1, node_janela, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, total_free_removed1, total_setup_removed1 = DesalocarProjetoPorNode(s_removed1, 
                                                                                projeto1, node1_use, sonda, desloc, 
                                                                                dados, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, 
                                                                                total_free_removed1, total_setup_removed1, debug)
                timer_remove.stop()
                
                # se não conseguir remover, vai para o próximo node
                if (flag1 == False):
                    continue
                
                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                outfile = open(filename, 'wb')
                pickle.dump(s_removed1, outfile)
                outfile.close()
                
                for el1 in remove_dict[projeto1]:
                    
                    projeto2, _, _ = el1
                    
                    timer_copy.start()
                    #s_removed2 = copy.deepcopy(s_removed1)
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                    infile = open(filename, 'rb')
                    s_removed2 = pickle.load(infile)
                    infile.close()
                    
                    gastos_removed2 = copy.copy(gastos_removed1)
                    sondas_removed2 = copy.deepcopy(sondas_removed1)
                    f_removed2 = copy.copy(f_removed1)
                    max_free_removed2 = copy.copy(max_free_removed1)
                    total_free_removed2 = copy.copy(total_free_removed1)
                    total_setup_removed2 = copy.copy(total_setup_removed1)
                    timer_copy.stop()
                    
                    timer_find.start()
                    for node2_use in s_removed2[sonda]:
                        if (projeto2 == node2_use.data[0]):
                            break
                    timer_find.stop()
                    
                    # otimização 1
                    if ( tuple(sorted((projeto1, projeto2))) in pular1 ):
                        continue
                    else:
                        pular1.add(tuple(sorted((projeto1, projeto2))))
                    
                    timer_remove.start()
                    s_removed2, flag2, node_janela, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, total_free_removed2, total_setup_removed2 = DesalocarProjetoPorNode(s_removed2, 
                                                                                    projeto2, node2_use, sonda, desloc, 
                                                                                    dados, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, 
                                                                                    total_free_removed2, total_setup_removed2, debug)
                    timer_remove.stop()
                    
                    # se não conseguir remover, vai para o próximo node
                    if (flag2 == False):
                        continue
                    
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                    outfile = open(filename, 'wb')
                    pickle.dump(s_removed2, outfile)
                    outfile.close()
                    
                    # enumerar projetos não alocados
                    for el2 in swap_2x1_fo_dict[(projeto1, projeto2)]:
                        
                        projeto3, _, _ = el2
                        
                        proc3 = dados[21][projeto3]
                        
                        # pular se ultrapassa limite de gastos
                        if (gastos_removed2 + dados[20][projeto3] > custo_total):
                            continue
                        
                        # tentar inserir na sonda do projeto que foi removido
                        for el3 in insert_fo_dict[projeto3]:
                            
                            if (el3[0] == -1):
                                _, sonda2, release3, due3 = el3
                                flag_el3 = "janela"
                            else:
                                projeto4, sonda2, _ = el3
                                flag_el3 = "projeto"
                            
                            if (sonda2 != sonda):
                                continue
                            
                            aloc3 = False
                            
                            timer_copy.start()
                            #s_local = copy.deepcopy(s_removed2)
                            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                            infile = open(filename, 'rb')
                            s_local = pickle.load(infile)
                            infile.close()
                            
                            gastos_local = copy.copy(gastos_removed2)
                            sondas_local = copy.deepcopy(sondas_removed2)
                            f_local = copy.copy(f_removed2)
                            max_free_local = copy.copy(max_free_removed2)
                            total_free_local = copy.copy(total_free_removed2)
                            total_setup_local = copy.copy(total_setup_removed2)
                            timer_copy.stop()

                            tam_prev = [v for (v,k) in sondas_local if (k==sonda)][0]
                            sondas_local.remove((tam_prev, sonda))
                            heapq.heapify(sondas_local)
                            
                            timer_find.start()
                            #if (flag_el3 == "janela"):
                            #    for node3_use in s_local[sonda]:
                            #        if ((release3 == node3_use.data[1]) and (due3 == node3_use.data[2])):
                            #            break
                            if (flag_el3 == "projeto"):
                                for node3_use in s_local[sonda]:
                                    if (projeto4 == node3_use.data[0]):
                                        break
                            timer_find.stop()
                            
                            timer_insere.start()
                            #if (flag_el3 == "janela"):
                            #    aloc3, gastos_local, sondas_local, f_local, total_free_local, total_setup_local, max_free_local = TentaInserirNodeDeJanela(s_local, node3_use, sonda, projeto3, dados, lag, desloc, proc3, aloc3, gastos_local, sondas_local, f_local, max_free_local, total_free_local, total_setup_local, tam_prev, debug)
                            
                            if (flag_el3 == "projeto"):
                                aloc3, gastos_local, sondas_local, f_local, total_free_local, total_setup_local, max_free_local = TentaInserirNodeDeProjeto(s_local, node3_use, sonda, projeto3, dados, lag, desloc, proc3, aloc3, gastos_local, f_local, sondas_local, max_free_local, total_free_local, total_setup_local, tam_prev, debug)
                            timer_insere.stop()
                            
                            if (aloc3):

                                if (f_local > f_best):

                                    if (debug):
                                        print ("Solução vizinha encontrada com melhor fitness")

                                    s_best = copy.deepcopy(s_local)
                                    gastos_best = copy.copy(gastos_local)
                                    sondas_best = copy.deepcopy(sondas_local)
                                    f_best = copy.copy(f_local)
                                    max_free_best = copy.copy(max_free_local)
                                    total_free_best = copy.copy(total_free_local)
                                    total_setup_best = copy.copy(total_setup_local)

                                elif (f_local == f_best):

                                    if (gastos_local < gastos_best):

                                        if (debug):
                                            print ("Solução vizinha encontrada com melhor gastos")

                                        s_best = copy.deepcopy(s_local)
                                        gastos_best = copy.copy(gastos_local)
                                        sondas_best = copy.deepcopy(sondas_local)
                                        f_best = copy.copy(f_local)
                                        max_free_best = copy.copy(max_free_local)
                                        total_free_best = copy.copy(total_free_local)
                                        total_setup_best = copy.copy(total_setup_local)

                                    elif (gastos_local == gastos_best):

                                        if (total_free_local > total_free_best):

                                            if (debug):
                                                print ("Solução vizinha encontrada com melhor total_free")

                                            s_best = copy.deepcopy(s_local)
                                            gastos_best = copy.copy(gastos_local)
                                            sondas_best = copy.deepcopy(sondas_local)
                                            f_best = copy.copy(f_local)
                                            max_free_best = copy.copy(max_free_local)
                                            total_free_best = copy.copy(total_free_local)
                                            total_setup_best = copy.copy(total_setup_local)

                                        elif (total_free_local == total_free_best):

                                            if (-max_free_local > -max_free_best):

                                                if (debug):
                                                    print ("Solução vizinha encontrada com melhor max_free")

                                                s_best = copy.deepcopy(s_local)
                                                gastos_best = copy.copy(gastos_local)
                                                sondas_best = copy.deepcopy(sondas_local)
                                                f_best = copy.copy(f_local)
                                                max_free_best = copy.copy(max_free_local)
                                                total_free_best = copy.copy(total_free_local)
                                                total_setup_best = copy.copy(total_setup_local)

                                            elif (-max_free_local == -max_free_best):

                                                if (total_setup_local < total_setup_best):

                                                    if (debug):
                                                        print ("Solução vizinha encontrada com melhor total_setup")

                                                    s_best = copy.deepcopy(s_local)
                                                    gastos_best = copy.copy(gastos_local)
                                                    sondas_best = copy.deepcopy(sondas_local)
                                                    f_best = copy.copy(f_local)
                                                    max_free_best = copy.copy(max_free_local)
                                                    total_free_best = copy.copy(total_free_local)
                                                    total_setup_best = copy.copy(total_setup_local)
    
    tempo_total = timer_geral.get_time(reference = "total", unit = "seconds")
    tempo_find = timer_find.get_time(reference = "total", unit = "seconds")
    tempo_insere = timer_insere.get_time(reference = "total", unit = "seconds")
    tempo_remove = timer_remove.get_time(reference = "total", unit = "seconds")
    tempo_copy = timer_copy.get_time(reference = "total", unit = "seconds")
    tempos = (tempo_preproc, tempo_total, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if (debug):
        print ("Solução final tem:")
        print ("f =", f_best)
        print ("gastos =", gastos_best)
        print ("total_free =", total_free_best)
        print ("max_free =", max_free_best)
        print ("total_setup =", total_setup_best)
        print ("sondas:", sondas)
        print ("Tempo gasto no swap_2x1_fo: ", tempo_total)
    
    return s_best, gastos_best, sondas_best, f_best, max_free_best, total_free_best, total_setup_best, tempos

def swap_2x2_fo(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, custo_total, debug=False, k=5):
    
    """
    Documentação: 
    
    Tenta trocar dois projetos alocados por dois não alocados.
    
    """
    
    if (debug):
        print ("Rodando estrutura de vizinhança: swapFO(2, 2)")
        print ("Solução inicial tem:")
        print ("f =", f)
        print ("gastos =", gastos)
        print ("total_free =", total_free)
        print ("max_free =", max_free)
        print ("total_setup =", total_setup)
        print ("sondas:", sondas)
    
    import pickle
    import copy
    import heapq
    import CPUtimer
    from time import process_time
    
    s_best = copy.deepcopy(s)
    gastos_best = copy.copy(gastos)
    sondas_best = copy.deepcopy(sondas)
    f_best = copy.copy(f)
    max_free_best = copy.copy(max_free)
    total_free_best = copy.copy(total_free)
    total_setup_best = copy.copy(total_setup)
    
    # gera conjunto de projetos já alocados
    proj_usados = set()
    for sonda in s.keys():
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_usados.add(node.data[0])
    
    # gera conjunto de projetos não alocados
    proj_nao_usados = set()
    for j in range(len(dados[4])):
        if j not in proj_usados:
            if (dados[19][j] > 0):
                proj_nao_usados.add(j)
    
    ans = PreProcessamento(s, desloc, dados, lag, proj_nao_usados, k=k, debug=debug)
    shift_dict, remove_dict, swap_dict, reinsert_dict, insert_fo_dict, swap_1x1_fo_dict, swap_1x2_fo_dict, swap_2x1_fo_dict, swap_2x2_fo_dict, tempo_preproc = ans
    
    timer_geral = CPUtimer.CPUTimer()
    timer_geral.reset()
    timer_geral.start()
    
    timer_find = CPUtimer.CPUTimer()
    timer_find.reset()
    
    timer_insere = CPUtimer.CPUTimer()
    timer_insere.reset()
    
    timer_remove = CPUtimer.CPUTimer()
    timer_remove.reset()
    
    timer_copy = CPUtimer.CPUTimer()
    timer_copy.reset()
    
    # otimização 1
    pular1 = set()
    pular2 = set()
    
    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
    outfile = open(filename, 'wb')
    pickle.dump(s, outfile)
    outfile.close()
    
    # enumera todos os projetos que posso tentar remover
    for sonda in s.keys():
        for node1 in s[sonda]:
            
            timer_copy.start()
            #s_removed1 = copy.deepcopy(s)
            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data1.pkl'
            infile = open(filename, 'rb')
            s_removed1 = pickle.load(infile)
            infile.close()
            
            gastos_removed1 = copy.copy(gastos)
            sondas_removed1 = copy.deepcopy(sondas)
            f_removed1 = copy.copy(f)
            max_free_removed1 = copy.copy(max_free)
            total_free_removed1 = copy.copy(total_free)
            total_setup_removed1 = copy.copy(total_setup)
            timer_copy.stop()
            
            if (node1.data[0] != -1):
                
                timer_find.start()
                for node1_use in s_removed1[sonda]:
                    if (node1.data[0] == node1_use.data[0]):
                        break
                timer_find.stop()
                
                timer_remove.start()
                # tenta remover
                projeto1 = node1.data[0]
                
                s_removed1, flag1, node_janela, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, total_free_removed1, total_setup_removed1 = DesalocarProjetoPorNode(s_removed1, 
                                                                                projeto1, node1_use, sonda, desloc, 
                                                                                dados, gastos_removed1, sondas_removed1, f_removed1, max_free_removed1, 
                                                                                total_free_removed1, total_setup_removed1, debug)
                timer_remove.stop()
                
                # se não conseguir remover, vai para o próximo node
                if (flag1 == False):
                    continue
                
                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                outfile = open(filename, 'wb')
                pickle.dump(s_removed1, outfile)
                outfile.close()
                
                for el1 in remove_dict[projeto1]:
                    
                    projeto2, _, _ = el1
                    
                    timer_copy.start()
                    #s_removed2 = copy.deepcopy(s_removed1)
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data2.pkl'
                    infile = open(filename, 'rb')
                    s_removed2 = pickle.load(infile)
                    infile.close()
                    
                    gastos_removed2 = copy.copy(gastos_removed1)
                    sondas_removed2 = copy.deepcopy(sondas_removed1)
                    f_removed2 = copy.copy(f_removed1)
                    max_free_removed2 = copy.copy(max_free_removed1)
                    total_free_removed2 = copy.copy(total_free_removed1)
                    total_setup_removed2 = copy.copy(total_setup_removed1)
                    timer_copy.stop()
                    
                    timer_find.start()
                    for node2_use in s_removed2[sonda]:
                        if (projeto2 == node2_use.data[0]):
                            break
                    timer_find.stop()
                    
                    # otimização 1
                    if ( tuple(sorted((projeto1, projeto2))) in pular1 ):
                        continue
                    else:
                        pular1.add(tuple(sorted((projeto1, projeto2))))
                    
                    timer_remove.start()
                    s_removed2, flag2, node_janela, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, total_free_removed2, total_setup_removed2 = DesalocarProjetoPorNode(s_removed2, 
                                                                                    projeto2, node2_use, sonda, desloc, 
                                                                                    dados, gastos_removed2, sondas_removed2, f_removed2, max_free_removed2, 
                                                                                    total_free_removed2, total_setup_removed2, debug)
                    timer_remove.stop()
                    
                    # se não conseguir remover, vai para o próximo node
                    if (flag2 == False):
                        continue
                    
                    filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                    outfile = open(filename, 'wb')
                    pickle.dump(s_removed2, outfile)
                    outfile.close()
                    
                    # enumerar projetos não alocados
                    for el2 in swap_2x2_fo_dict[(projeto1, projeto2)]:
                        
                        projeto3, _, _ = el2
                        
                        proc3 = dados[21][projeto3]
                        
                        # pular se ultrapassa limite de gastos
                        if (gastos_removed2 + dados[20][projeto3] > custo_total):
                            continue
                        
                        # tentar inserir na sonda do projeto que foi removido
                        for el3 in insert_fo_dict[projeto3]:
                            
                            if (el3[0] == -1):
                                _, sonda2, release3, due3 = el3
                                flag_el3 = "janela"
                            else:
                                projeto5, sonda2, _ = el3
                                flag_el3 = "projeto"
                            
                            if (sonda2 != sonda):
                                continue
                            
                            aloc3 = False
                            
                            timer_copy.start()
                            #s_local1 = copy.deepcopy(s_removed2)
                            filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data3.pkl'
                            infile = open(filename, 'rb')
                            s_local1 = pickle.load(infile)
                            infile.close()
                    
                            gastos_local1 = copy.copy(gastos_removed2)
                            sondas_local1 = copy.deepcopy(sondas_removed2)
                            f_local1 = copy.copy(f_removed2)
                            max_free_local1 = copy.copy(max_free_removed2)
                            total_free_local1 = copy.copy(total_free_removed2)
                            total_setup_local1 = copy.copy(total_setup_removed2)
                            timer_copy.stop()
                            
                            tam_prev = [v for (v,k) in sondas_local1 if (k==sonda)][0]
                            sondas_local1.remove((tam_prev, sonda))
                            heapq.heapify(sondas_local1)
                            
                            timer_find.start()
                            #if (flag_el3 == "janela"):
                            #    for node3_use in s_local1[sonda]:
                            #        if ((release3 == node3_use.data[1]) and (due3 == node3_use.data[2])):
                            #            break
                            if (flag_el3 == "projeto"):
                                for node3_use in s_local1[sonda]:
                                    if (projeto5 == node3_use.data[0]):
                                        break
                            timer_find.stop()
                            
                            timer_insere.start()
                            #if (flag_el3 == "janela"):
                            #    aloc3, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeJanela(s_local1, node3_use, sonda, projeto3, dados, lag, desloc, proc3, aloc3, gastos_local1, sondas_local1, f_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev, debug)
                            
                            if (flag_el3 == "projeto"):
                                aloc3, gastos_local1, sondas_local1, f_local1, total_free_local1, total_setup_local1, max_free_local1 = TentaInserirNodeDeProjeto(s_local1, node3_use, sonda, projeto3, dados, lag, desloc, proc3, aloc3, gastos_local1, f_local1, sondas_local1, max_free_local1, total_free_local1, total_setup_local1, tam_prev, debug)
                            timer_insere.stop()
                            
                            if (aloc3):
                                
                                filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data4.pkl'
                                outfile = open(filename, 'wb')
                                pickle.dump(s_local1, outfile)
                                outfile.close()
                                
                                for el4 in swap_2x2_fo_dict[(projeto1, projeto2)]:
                                    
                                    projeto4, _, _ = el4
                                    
                                    if (projeto4 == projeto3):
                                        continue
                                    
                                    proc4 = dados[21][projeto4]
                                    
                                    # otimização 1
                                    if ( tuple(sorted((projeto3, projeto4))) in pular2 ):
                                        continue
                                    else:
                                        pular2.add(tuple(sorted((projeto3, projeto4))))
                                    
                                    # pular se ultrapassa limite de gastos
                                    if (gastos_local1 + dados[20][projeto4] > custo_total):
                                        continue
                                    
                                    # tentar inserir na sonda do projeto que foi removido
                                    for el5 in insert_fo_dict[projeto4]:
                                        
                                        if (el5[0] == -1):
                                            _, sonda3, release5, due5 = el5
                                            flag_el5 = "janela"
                                        else:
                                            projeto6, sonda3, _ = el5
                                            flag_el5 = "projeto"
                                        
                                        if (sonda3 != sonda):
                                            continue
                                        
                                        aloc4 = False
                                        
                                        timer_copy.start()
                                        #s_local2 = copy.deepcopy(s_local1)
                                        filename = '/home/joaoweissmann/Documents/synthetic_data_generator/data_temp/data4.pkl'
                                        infile = open(filename, 'rb')
                                        s_local2 = pickle.load(infile)
                                        infile.close()
                            
                                        gastos_local2 = copy.copy(gastos_local1)
                                        sondas_local2 = copy.deepcopy(sondas_local1)
                                        f_local2 = copy.copy(f_local1)
                                        max_free_local2 = copy.copy(max_free_local1)
                                        total_free_local2 = copy.copy(total_free_local1)
                                        total_setup_local2 = copy.copy(total_setup_local1)
                                        timer_copy.stop()
                                        
                                        tam_prev = [v for (v,k) in sondas_local2 if (k==sonda)][0]
                                        sondas_local2.remove((tam_prev, sonda))
                                        heapq.heapify(sondas_local2)
                                        
                                        timer_find.start()
                                        #if (flag_el5 == "janela"):
                                        #    for node4_use in s_local2[sonda]:
                                        #        if ((release5 == node4_use.data[1]) and (due5 == node4_use.data[2])):
                                        #            break
                                        if (flag_el5 == "projeto"):
                                            for node4_use in s_local2[sonda]:
                                                if (projeto6 == node4_use.data[0]):
                                                    break
                                        timer_find.stop()
                                        
                                        timer_insere.start()
                                        #if (flag_el5 == "janela"):
                                        #    aloc4, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeJanela(s_local2, node4_use, sonda, projeto4, dados, lag, desloc, proc4, aloc4, gastos_local2, sondas_local2, f_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev, debug)
                                        
                                        if (flag_el5 == "projeto"):
                                            aloc4, gastos_local2, sondas_local2, f_local2, total_free_local2, total_setup_local2, max_free_local2 = TentaInserirNodeDeProjeto(s_local2, node4_use, sonda, projeto4, dados, lag, desloc, proc4, aloc4, gastos_local2, f_local2, sondas_local2, max_free_local2, total_free_local2, total_setup_local2, tam_prev, debug)
                                        timer_insere.stop()
                                        
                                        if (aloc4):

                                            if (f_local2 > f_best):

                                                if (debug):
                                                    print ("Solução vizinha encontrada com melhor fitness")

                                                s_best = copy.deepcopy(s_local2)
                                                gastos_best = copy.copy(gastos_local2)
                                                sondas_best = copy.deepcopy(sondas_local2)
                                                f_best = copy.copy(f_local2)
                                                max_free_best = copy.copy(max_free_local2)
                                                total_free_best = copy.copy(total_free_local2)
                                                total_setup_best = copy.copy(total_setup_local2)

                                            elif (f_local2 == f_best):

                                                if (gastos_local2 < gastos_best):

                                                    if (debug):
                                                        print ("Solução vizinha encontrada com melhor gastos")

                                                    s_best = copy.deepcopy(s_local2)
                                                    gastos_best = copy.copy(gastos_local2)
                                                    sondas_best = copy.deepcopy(sondas_local2)
                                                    f_best = copy.copy(f_local2)
                                                    max_free_best = copy.copy(max_free_local2)
                                                    total_free_best = copy.copy(total_free_local2)
                                                    total_setup_best = copy.copy(total_setup_local2)

                                                elif (gastos_local2 == gastos_best):

                                                    if (total_free_local2 > total_free_best):

                                                        if (debug):
                                                            print ("Solução vizinha encontrada com melhor total_free")

                                                        s_best = copy.deepcopy(s_local2)
                                                        gastos_best = copy.copy(gastos_local2)
                                                        sondas_best = copy.deepcopy(sondas_local2)
                                                        f_best = copy.copy(f_local2)
                                                        max_free_best = copy.copy(max_free_local2)
                                                        total_free_best = copy.copy(total_free_local2)
                                                        total_setup_best = copy.copy(total_setup_local2)

                                                    elif (total_free_local2 == total_free_best):

                                                        if (-max_free_local2 > -max_free_best):

                                                            if (debug):
                                                                print ("Solução vizinha encontrada com melhor max_free")

                                                            s_best = copy.deepcopy(s_local2)
                                                            gastos_best = copy.copy(gastos_local2)
                                                            sondas_best = copy.deepcopy(sondas_local2)
                                                            f_best = copy.copy(f_local2)
                                                            max_free_best = copy.copy(max_free_local2)
                                                            total_free_best = copy.copy(total_free_local2)
                                                            total_setup_best = copy.copy(total_setup_local2)

                                                        elif (-max_free_local2 == -max_free_best):

                                                            if (total_setup_local2 < total_setup_best):

                                                                if (debug):
                                                                    print ("Solução vizinha encontrada com melhor total_setup")

                                                                s_best = copy.deepcopy(s_local2)
                                                                gastos_best = copy.copy(gastos_local2)
                                                                sondas_best = copy.deepcopy(sondas_local2)
                                                                f_best = copy.copy(f_local2)
                                                                max_free_best = copy.copy(max_free_local2)
                                                                total_free_best = copy.copy(total_free_local2)
                                                                total_setup_best = copy.copy(total_setup_local2)
    
    tempo_total = timer_geral.get_time(reference = "total", unit = "seconds")
    tempo_find = timer_find.get_time(reference = "total", unit = "seconds")
    tempo_insere = timer_insere.get_time(reference = "total", unit = "seconds")
    tempo_remove = timer_remove.get_time(reference = "total", unit = "seconds")
    tempo_copy = timer_copy.get_time(reference = "total", unit = "seconds")
    tempos = (tempo_preproc, tempo_total, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if (debug):
        print ("Solução final tem:")
        print ("f =", f_best)
        print ("gastos =", gastos_best)
        print ("total_free =", total_free_best)
        print ("max_free =", max_free_best)
        print ("total_setup =", total_setup_best)
        print ("sondas:", sondas)
        print ("Tempo gasto no swap_2x2_fo: ", tempo_total)
    
    return s_best, gastos_best, sondas_best, f_best, max_free_best, total_free_best, total_setup_best, tempos

def Perturbar(s, desloc, dados, gastos, sondas, f, max_free, total_free, total_setup, 
              n_projetos, n_sondas, n_periodos, custo_total, criterio='lucro/custo', alpha=0.5, beta=0.5, 
              debug=False):
    
    """
    Documentação: 
    
    Recebe um solução e perturba esta solução, descontruindo parte dela e reconstruindo novamente.
    
    """
    
    import CPUtimer
    
    if (debug):
        timer = CPUtimer.CPUTimer()
        timer.reset()
        timer.start()
    
    if (debug):
        print ("Rodando perturbação")
        print ("Solução inicial tem:")
        print ("f =", f)
        print ("gastos =", gastos)
        print ("total_free =", total_free)
        print ("max_free =", max_free)
        print ("total_setup =", total_setup)
        print ("sondas:", sondas)
    
    proj_count = 0
    for sonda in range(len(s.keys())):
        for node in s[sonda]:
            if (node.data[0] != -1):
                proj_count += 1
    
    k = max(0, proj_count // (1/beta))
    
    if (k > 0):
        
        if (debug):
            print ("Desconstruindo parcialmente a solução: removendo ", k, " projetos.")
        
        # remover k projetos aleatoriamente
        s, gastos, sondas, f, max_free, total_free, total_setup = Remover_Projetos(s, k, desloc, dados, gastos, sondas, f, max_free, total_free, total_setup, debug)

        if (debug):
            print ("Reconstruindo solução...")

        # reconstruir solução
        f_new, gastos_new, s_new, _, sondas_new, total_free_new, total_setup_new, max_free_new, _ = ConstruirSolucao(dados, n_projetos,
                                                                                             n_sondas, 
                                                                                             n_periodos, 
                                                                                             custo_total, 
                                                                                             desloc,
                                                                                             criterio=criterio, alpha=alpha, s=s,
                                                                                             debug=debug)
        
        if debug:
            tempo_total = timer.get_time(reference = "total", unit = "seconds")
            print ("Tempo gasto na perturbação1: ", tempo_total)
        
        if (debug):
            print ("Solução final tem:")
            print ("f =", f_new)
            print ("gastos =", gastos_new)
            print ("total_free =", total_free_new)
            print ("max_free =", max_free_new)
            print ("total_setup =", total_setup_new)
            print ("sondas:", sondas_new)

        return s_new, gastos_new, sondas_new, f_new, max_free_new, total_free_new, total_setup_new
    
    else:
        
        if debug:
            tempo_total = timer.get_time(reference = "total", unit = "seconds")
            print ("Tempo gasto na perturbação1: ", tempo_total)
        
        return s, gastos, sondas, f, max_free, total_free, total_setup

def BuscaLocal(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, custo_total,
               vizinhanca='shift_1x0_interrota', debug=False, k=5):
    
    """
    Documentação:
    
    vizinhancas = ['shift_1x0_interrota', 'shift_2x0_interrota', 
                   'swap_1x1_interrota', 'swap_2x1_interrota', 'swap_2x2_interrota', 
                   'reinsercao_1_intrarota', 'reinsercao_2_intrarota', 
                   'inserir_novo_fo', 'swap_1x1_fo', 'swap_2x1_fo', 'swap_1x2_fo', 'swap_2x2_fo']
    
    """
    
    import copy
    import CPUtimer
    
    if (debug):
        timer = CPUtimer.CPUTimer()
        timer.reset()
        timer.start()
    
    tempo_preproc, tempo_busca, tempo_find, tempo_insere, tempo_remove, tempo_copy = 0, 0, 0, 0, 0, 0
    delta = 1
    while (delta > 0.001):
        
        f_old = copy.copy(f)
        gastos_old = copy.copy(gastos)
        total_free_old = copy.copy(total_free)
        total_setup_old = copy.copy(total_setup)
        max_free_old = copy.copy(max_free)
        
        if (vizinhanca == 'shift_1x0_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = shift_1x0_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        elif (vizinhanca == 'shift_2x0_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = shift_2x0_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'swap_1x1_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_1x1_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'swap_2x1_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_2x1_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'swap_2x2_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_2x2_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'reinsercao_1_intrarota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = reinsercao_1_intrarota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'reinsercao_2_intrarota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = reinsercao_2_intrarota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'inserir_novo_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = inserir_novo_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        
        elif (vizinhanca == 'swap_1x1_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_1x1_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        
        elif (vizinhanca == 'swap_2x1_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_2x1_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        
        elif (vizinhanca == 'swap_1x2_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_1x2_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        elif (vizinhanca == 'swap_2x2_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_2x2_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        
        if (f > f_old):
            delta = f - f_old
            if (debug):
                print ("Solução vizinha com melhor fitness encontrada: delta =", delta)
        elif (f == f_old):
            if (gastos < gastos_old):
                delta = gastos_old - gastos
                if (debug):
                    print ("Solução vizinha com melhor gastos encontrada: delta =", delta)
            elif (gastos == gastos_old):
                if (total_free > total_free_old):
                    delta = total_free - total_free_old
                    if (debug):
                        print ("Solução vizinha com melhor total_free encontrada: delta =", delta)
                elif (total_free == total_free_old):
                    if (-max_free > -max_free_old):
                        delta = max_free_old - max_free
                        if (debug):
                            print ("Solução vizinha com melhor max_free encontrada: delta =", delta)
                    elif (-max_free == -max_free_old):
                        if (total_setup > total_setup_old):
                            delta = total_setup - total_setup_old
                            if (debug):
                                print ("Solução vizinha com melhor total_setup encontrada: delta =", delta)
                        else:
                            delta = 0
                    else:
                        delta = 0
                else:
                    delta = 0
            else:
                delta = 0
        else:
            delta = 0
    
        t_preproc, t_total, t_find, t_insere, t_remove, t_copy = tempos
        tempo_preproc += t_preproc
        tempo_busca += t_total
        tempo_find += t_find
        tempo_insere += t_insere
        tempo_remove += t_remove
        tempo_copy += t_copy
        
    tempos = (tempo_preproc, tempo_busca, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if debug:
        tempo_total = timer.get_time(reference = "total", unit = "seconds")
        print ("Tempo gasto na busca local: ", tempo_total)
    
    return s, gastos, sondas, f, max_free, total_free, total_setup, tempos

def BuscaVND(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, custo_total, debug=False, k=5):
    
    """
    Documentação: 
    """
    
    import copy
    import CPUtimer
    
    if (debug):
        timer = CPUtimer.CPUTimer()
        timer.reset()
        timer.start()
    
    if (debug):
        print ("Rodando busca VND")
    
    # inicializar lista de vizinhanças
    vizinhancas = ['shift_1x0_interrota', 'shift_2x0_interrota', 
                   'swap_1x1_interrota', 'swap_2x1_interrota', 'swap_2x2_interrota', 
                   'reinsercao_1_intrarota', 'reinsercao_2_intrarota', 
                   'inserir_novo_fo', 'swap_1x1_fo', 'swap_2x1_fo', 'swap_1x2_fo', 'swap_2x2_fo']
    
    tempo_preproc, tempo_busca, tempo_find, tempo_insere, tempo_remove, tempo_copy = 0, 0, 0, 0, 0, 0
    # enquanto lista de vizinhanças não está vazia
    while vizinhancas:
        
        f_old = copy.copy(f)
        gastos_old = copy.copy(gastos)
        total_free_old = copy.copy(total_free)
        total_setup_old = copy.copy(total_setup)
        max_free_old = copy.copy(max_free)
        
        # seleciona vizinhança N()
        vizinhanca = vizinhancas[0]
        
        if (debug):
            print ("Estrutura de vizinhança escolhida: ", vizinhanca)
        
        # encontre melhor vizinho s' em N(s)
        
        if (vizinhanca == 'shift_1x0_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = shift_1x0_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        elif (vizinhanca == 'shift_2x0_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = shift_2x0_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'swap_1x1_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_1x1_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'swap_2x1_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_2x1_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'swap_2x2_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_2x2_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'reinsercao_1_intrarota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = reinsercao_1_intrarota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'reinsercao_2_intrarota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = reinsercao_2_intrarota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'inserir_novo_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = inserir_novo_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        
        elif (vizinhanca == 'swap_1x1_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_1x1_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        
        elif (vizinhanca == 'swap_2x1_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_2x1_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        
        elif (vizinhanca == 'swap_1x2_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_1x2_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        elif (vizinhanca == 'swap_2x2_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_2x2_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        
        
        # se fo(s') melhor que fo(s)
        improv_flag = False
        if (f > f_old):
            improv_flag = True
            delta = f - f_old
            if (debug):
                print ("Solução vizinha com melhor fitness encontrada: delta =", delta)
        elif (f == f_old):
            if (gastos < gastos_old):
                improv_flag = True
                delta = 0 # gastos_old - gastos
                if (debug):
                    print ("Solução vizinha com melhor gastos encontrada: delta =", delta)
            elif (gastos == gastos_old):
                if (total_free > total_free_old):
                    improv_flag = True
                    delta = 0 # total_free - total_free_old
                    if (debug):
                        print ("Solução vizinha com melhor total_free encontrada: delta =", delta)
                elif (total_free == total_free_old):
                    if (-max_free > -max_free_old):
                        improv_flag = True
                        delta = 0 # max_free_old - max_free
                        if (debug):
                            print ("Solução vizinha com melhor max_free encontrada: delta =", delta)
                    elif (-max_free == -max_free_old):
                        if (total_setup > total_setup_old):
                            improv_flag = True
                            delta = 0 # total_setup - total_setup_old
                            if (debug):
                                print ("Solução vizinha com melhor total_setup encontrada: delta =", delta)
                        else:
                            delta = 0
                    else:
                        delta = 0
                else:
                    delta = 0
            else:
                delta = 0
        else:
            delta = 0
        
        if (delta < 0.1):
            improv_flag = False
        
        # se o movimento melhorou a solução
        if(improv_flag):
            # atualizar lista de vizinhanças
            vizinhancas = ['shift_1x0_interrota', 'shift_2x0_interrota', 
                           'swap_1x1_interrota', 'swap_2x1_interrota', 'swap_2x2_interrota', 
                           'reinsercao_1_intrarota', 'reinsercao_2_intrarota', 
                           'inserir_novo_fo', 'swap_1x1_fo', 'swap_2x1_fo', 'swap_1x2_fo', 'swap_2x2_fo']
            
        else:
            # remove N() da lista de vizinhanças
            vizinhancas.remove(vizinhanca)
        
        t_preproc, t_total, t_find, t_insere, t_remove, t_copy = tempos
        tempo_preproc += t_preproc
        tempo_busca += t_total
        tempo_find += t_find
        tempo_insere += t_insere
        tempo_remove += t_remove
        tempo_copy += t_copy
        
    tempos = (tempo_preproc, tempo_busca, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    
    if debug:
        tempo_total = timer.get_time(reference = "total", unit = "seconds")
        print ("Tempo gasto na busca VND: ", tempo_total)
    
    return s, gastos, sondas, f, max_free, total_free, total_setup, tempos

def BuscaRVND(s, gastos, sondas, f, max_free, total_free, total_setup, dados, lag, desloc, custo_total, debug=False, k=5):
    
    """
    Documentação: 
    """
    
    import copy
    import numpy as np
    import CPUtimer
    
    if (debug):
        timer = CPUtimer.CPUTimer()
        timer.reset()
        timer.start()
    
    if (debug):
        print ("Rodando busca RVND")
    
    # inicializar lista de vizinhanças
    vizinhancas = ['shift_1x0_interrota', 'shift_2x0_interrota', 
                   'swap_1x1_interrota', 'swap_2x1_interrota', 'swap_2x2_interrota', 
                   'reinsercao_1_intrarota', 'reinsercao_2_intrarota', 
                   'inserir_novo_fo', 'swap_1x1_fo', 'swap_2x1_fo', 'swap_1x2_fo', 'swap_2x2_fo']
    
    tempo_preproc, tempo_busca, tempo_find, tempo_insere, tempo_remove, tempo_copy = 0, 0, 0, 0, 0, 0
    # enquanto lista de vizinhanças não está vazia
    while vizinhancas:
        
        f_old = copy.copy(f)
        gastos_old = copy.copy(gastos)
        total_free_old = copy.copy(total_free)
        total_setup_old = copy.copy(total_setup)
        max_free_old = copy.copy(max_free)
        
        # seleciona vizinhança N()
        vizinhanca = np.random.choice(vizinhancas)
        
        if (debug):
            print ("Estrutura de vizinhança escolhida: ", vizinhanca)
        
        # encontre melhor vizinho s' em N(s)
        
        if (vizinhanca == 'shift_1x0_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = shift_1x0_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        elif (vizinhanca == 'shift_2x0_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = shift_2x0_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'swap_1x1_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_1x1_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'swap_2x1_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_2x1_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'swap_2x2_interrota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_2x2_interrota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'reinsercao_1_intrarota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = reinsercao_1_intrarota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'reinsercao_2_intrarota'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = reinsercao_2_intrarota(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, debug, k)
        
        elif (vizinhanca == 'inserir_novo_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = inserir_novo_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        
        elif (vizinhanca == 'swap_1x1_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_1x1_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        
        elif (vizinhanca == 'swap_2x1_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_2x1_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        
        elif (vizinhanca == 'swap_1x2_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_1x2_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        elif (vizinhanca == 'swap_2x2_fo'):
            
            s, gastos, sondas, f, max_free, total_free, total_setup, tempos = swap_2x2_fo(s, gastos, sondas, 
                                                                                          f, max_free, total_free, 
                                                                                          total_setup, dados, lag, 
                                                                                          desloc, custo_total, debug, k)
        
        # se fo(s') melhor que fo(s)
        improv_flag = False
        if (f > f_old):
            improv_flag = True
            delta = f - f_old
            if (debug):
                print ("Solução vizinha com melhor fitness encontrada: delta =", delta)
        elif (f == f_old):
            if (gastos < gastos_old):
                improv_flag = True
                delta = 0 # gastos_old - gastos
                if (debug):
                    print ("Solução vizinha com melhor gastos encontrada: delta =", delta)
            elif (gastos == gastos_old):
                if (total_free > total_free_old):
                    improv_flag = True
                    delta = 0 # total_free - total_free_old
                    if (debug):
                        print ("Solução vizinha com melhor total_free encontrada: delta =", delta)
                elif (total_free == total_free_old):
                    if (-max_free > -max_free_old):
                        improv_flag = True
                        delta = 0 # max_free_old - max_free
                        if (debug):
                            print ("Solução vizinha com melhor max_free encontrada: delta =", delta)
                    elif (-max_free == -max_free_old):
                        if (total_setup > total_setup_old):
                            improv_flag = True
                            delta = 0 # total_setup - total_setup_old
                            if (debug):
                                print ("Solução vizinha com melhor total_setup encontrada: delta =", delta)
                        else:
                            delta = 0
                    else:
                        delta = 0
                else:
                    delta = 0
            else:
                delta = 0
        else:
            delta = 0
        
        if (delta < 0.1):
            improv_flag = False
        
        # se o movimento melhorou a solução
        if(improv_flag):
            # atualizar lista de vizinhanças
            vizinhancas = ['shift_1x0_interrota', 'shift_2x0_interrota', 
                           'swap_1x1_interrota', 'swap_2x1_interrota', 'swap_2x2_interrota', 
                           'reinsercao_1_intrarota', 'reinsercao_2_intrarota', 
                           'inserir_novo_fo', 'swap_1x1_fo', 'swap_2x1_fo', 'swap_1x2_fo', 'swap_2x2_fo']
            
        else:
            # remove N() da lista de vizinhanças
            vizinhancas.remove(vizinhanca)
        
        t_preproc, t_total, t_find, t_insere, t_remove, t_copy = tempos
        tempo_preproc += t_preproc
        tempo_busca += t_total
        tempo_find += t_find
        tempo_insere += t_insere
        tempo_remove += t_remove
        tempo_copy += t_copy
    
    tempos = (tempo_preproc, tempo_busca, tempo_find, tempo_insere, tempo_remove, tempo_copy)
    
    if debug:
        tempo_total = timer.get_time(reference = "total", unit = "seconds")
        print ("Tempo gasto na busca RVND: ", tempo_total)
    
    return s, gastos, sondas, f, max_free, total_free, total_setup, tempos

def GRASP_VND(arquivo, n_iter=100, criterios=None, alpha=0.5, print_sol=True, debug=False, k=5):
    
    """
    Documentação:
    """
    
    import CPUtimer
    import copy
    import numpy as np
    
    print ("Rodando GRASP_VND...")
    
    if criterios == None:
        criterios = ['lucro/custo', 'lucro/duracao', 'lucro', 'custo', 'duracao', 'janela']
    
    n_projetos, n_sondas, n_periodos, t_init, t_final, delta_t, custo_total, dados, desloc = Read_data(path=arquivo)
    
    lag = n_sondas
    
    tempo_construcao, tempo_preproc, tempo_busca, tempo_find, tempo_insere, tempo_remove, tempo_copy = 0, 0, 0, 0, 0, 0, 0
    
    criterio = np.random.choice(criterios)
    
    f, gastos , s, s_candidatos, sondas, total_free, total_setup, max_free, t_construcao = ConstruirSolucao(dados, 
                                                                           n_projetos, n_sondas, 
                                                                           n_periodos, custo_total, desloc,
                                                                           criterio=criterio, alpha=alpha,
                                                                                             debug=debug)
    tempo_construcao += t_construcao
    
    best_f = copy.deepcopy(f)
    best_gastos = copy.deepcopy(gastos)
    best_s = copy.deepcopy(s)
    best_total_free = copy.deepcopy(total_free)
    best_total_setup = copy.deepcopy(total_setup)
    best_max_free = copy.deepcopy(max_free)
    best_sondas = copy.deepcopy(sondas)
    
    timer = CPUtimer.CPUTimer()
    timer.reset()
    timer.start()
    
    i = 1
    while(n_iter >= i):
        
        # print ("Iteração: ", i)
        
        i += 1
        
        criterio = np.random.choice(criterios)
        
        alpha = np.random.choice([0.8, 0.85, 0.9, 0.95, 0.99])
        
        f, gastos , s, _, sondas, total_free, total_setup, max_free, t_construcao = ConstruirSolucao(dados, n_projetos, n_sondas, 
                                                                               n_periodos, custo_total, desloc,
                                                                               criterio=criterio, alpha=alpha,
                                                                                      debug=debug)
        
        s, gastos, sondas, f, max_free, total_free, total_setup, tempos = BuscaVND(s, gastos, sondas, f, max_free, 
                                                                        total_free, total_setup, dados, 
                                                                        lag, desloc, custo_total, debug, k)
        
        tempo_construcao += t_construcao
        t_preproc, t_total, t_find, t_insere, t_remove, t_copy = tempos
        tempo_preproc += t_preproc
        tempo_busca += t_total
        tempo_find += t_find
        tempo_insere += t_insere
        tempo_remove += t_remove
        tempo_copy += t_copy
        
        if (f > best_f):
            best_f = copy.deepcopy(f)
            best_gastos = copy.deepcopy(gastos)
            best_s = copy.deepcopy(s)
            best_total_free = copy.deepcopy(total_free)
            best_total_setup = copy.deepcopy(total_setup)
            best_max_free = copy.deepcopy(max_free)
            best_sondas = copy.deepcopy(sondas)
    
    tempos_return = {"tempo_construcao": tempo_construcao,
                     "tempo_preproc": tempo_preproc,
                     "tempo_busca": tempo_busca,
                     "tempo_find": tempo_find,
                     "tempo_insere": tempo_insere,
                     "tempo_remove": tempo_remove, 
                     "tempo_copy": tempo_copy}
    
    check = VerificaRestricoes(best_s, dados, best_f, best_gastos, desloc, best_sondas, 
                               best_max_free, best_total_free, best_total_setup, debug)
    
    tempo_total = timer.get_time(reference = "total", unit = "seconds")
    tempo_medio = timer.get_time(reference = "average", unit = "seconds")
    
    print ("GRASP_VND finalizado.")
    
    if check:
        check_str = 'feasible'
    else:
        check_str = 'not feasible'
    
    if print_sol:
        print (check_str)
        print ('fitness: ', best_f)
        print ('gastos: ', best_gastos)
        print ('tempo total de execução (segundos) : ', tempo_total)
        print ('tempo médio de execução (segundos) ', tempo_medio)
        for i in range(n_sondas):
            for node in best_s[i]:
                print ('sonda ', i, ' executa projetos: ', node.data)
    
    return best_f, best_gastos, best_s, tempo_total, tempo_medio, check_str, tempos_return

def GRASP_RVND(arquivo, n_iter=100, criterios=None, alpha=0.5, print_sol=True, debug=False, k=5):
    
    """
    Documentação:
    """
    
    import CPUtimer
    import copy
    import numpy as np
    
    print ("Rodando GRASP_RVND...")
    
    if criterios == None:
        criterios = ['lucro/custo', 'lucro/duracao', 'lucro', 'custo', 'duracao', 'janela']
    
    n_projetos, n_sondas, n_periodos, t_init, t_final, delta_t, custo_total, dados, desloc = Read_data(path=arquivo)
    
    lag = n_sondas
    
    tempo_construcao, tempo_preproc, tempo_busca, tempo_find, tempo_insere, tempo_remove, tempo_copy = 0, 0, 0, 0, 0, 0, 0
    
    criterio = np.random.choice(criterios)
    
    f, gastos , s, s_candidatos, sondas, total_free, total_setup, max_free, t_construcao = ConstruirSolucao(dados, 
                                                                           n_projetos, n_sondas, 
                                                                           n_periodos, custo_total, desloc,
                                                                           criterio=criterio, alpha=alpha,
                                                                                             debug=debug)
    tempo_construcao += t_construcao
    
    best_f = copy.deepcopy(f)
    best_gastos = copy.deepcopy(gastos)
    best_s = copy.deepcopy(s)
    best_total_free = copy.deepcopy(total_free)
    best_total_setup = copy.deepcopy(total_setup)
    best_max_free = copy.deepcopy(max_free)
    best_sondas = copy.deepcopy(sondas)
    
    timer = CPUtimer.CPUTimer()
    timer.reset()
    timer.start()
    
    i = 1
    while(n_iter >= i):
        
        # print ("Iteração: ", i)
        
        i += 1
        
        criterio = np.random.choice(criterios)
        
        alpha = np.random.choice([0.8, 0.85, 0.9, 0.95, 0.99])
        
        f, gastos , s, _, sondas, total_free, total_setup, max_free, t_construcao = ConstruirSolucao(dados, n_projetos, n_sondas, 
                                                                               n_periodos, custo_total, desloc,
                                                                               criterio=criterio, alpha=alpha,
                                                                                      debug=debug)
        
        s, gastos, sondas, f, max_free, total_free, total_setup, tempos = BuscaRVND(s, gastos, sondas, f, max_free, 
                                                                        total_free, total_setup, dados, 
                                                                        lag, desloc, custo_total, debug, k)
        
        tempo_construcao += t_construcao
        t_preproc, t_total, t_find, t_insere, t_remove, t_copy = tempos
        tempo_preproc += t_preproc
        tempo_busca += t_total
        tempo_find += t_find
        tempo_insere += t_insere
        tempo_remove += t_remove
        tempo_copy += t_copy
        
        if (f > best_f):
            best_f = copy.deepcopy(f)
            best_gastos = copy.deepcopy(gastos)
            best_s = copy.deepcopy(s)
            best_total_free = copy.deepcopy(total_free)
            best_total_setup = copy.deepcopy(total_setup)
            best_max_free = copy.deepcopy(max_free)
            best_sondas = copy.deepcopy(sondas)
    
    tempos_return = {"tempo_construcao": tempo_construcao,
                     "tempo_preproc": tempo_preproc,
                     "tempo_busca": tempo_busca,
                     "tempo_find": tempo_find,
                     "tempo_insere": tempo_insere,
                     "tempo_remove": tempo_remove,
                     "tempo_copy": tempo_copy}
    
    check = VerificaRestricoes(best_s, dados, best_f, best_gastos, desloc, best_sondas, 
                               best_max_free, best_total_free, best_total_setup, debug)
    
    tempo_total = timer.get_time(reference = "total", unit = "seconds")
    tempo_medio = timer.get_time(reference = "average", unit = "seconds")
    
    print ("GRASP_RVND finalizado.")
    
    if check:
        check_str = 'feasible'
    else:
        check_str = 'not feasible'
    
    if print_sol:
        print (check_str)
        print ('fitness: ', best_f)
        print ('gastos: ', best_gastos)
        print ('tempo total de execução (segundos) : ', tempo_total)
        print ('tempo médio de execução (segundos) ', tempo_medio)
        for i in range(n_sondas):
            for node in best_s[i]:
                print ('sonda ', i, ' executa projetos: ', node.data)
    
    return best_f, best_gastos, best_s, tempo_total, tempo_medio, check_str, tempos_return

def ILS_VND(arquivo, n_iter=100, criterios=None, alpha=0.5, beta=0.5, print_sol=True, debug=False, k=5):
    
    """
    Documentação:
    """
    
    import CPUtimer
    import copy
    import numpy as np
    
    print ("Rodando ILS_VND...")
    
    if criterios == None:
        criterios = ['lucro/custo', 'lucro/duracao', 'lucro', 'custo', 'duracao', 'janela']
    
    n_projetos, n_sondas, n_periodos, t_init, t_final, delta_t, custo_total, dados, desloc = Read_data(path=arquivo)
    
    lag = n_sondas
    
    tempo_construcao, tempo_preproc, tempo_busca, tempo_find, tempo_insere, tempo_remove, tempo_copy = 0, 0, 0, 0, 0, 0, 0
    
    criterio = np.random.choice(criterios)
    
    f, gastos , s, s_candidatos, sondas, total_free, total_setup, max_free, t_construcao = ConstruirSolucao(dados, 
                                                                           n_projetos, n_sondas, 
                                                                           n_periodos, custo_total, desloc,
                                                                           criterio=criterio, alpha=alpha,
                                                                                             debug=debug)
    
    s, gastos, sondas, f, max_free, total_free, total_setup, tempos = BuscaVND(s, gastos, sondas, f, max_free, 
                                                                        total_free, total_setup, dados, 
                                                                        lag, desloc, custo_total, debug, k)
    
    tempo_construcao += t_construcao
    t_preproc, t_total, t_find, t_insere, t_remove, t_copy = tempos
    tempo_preproc += t_preproc
    tempo_busca += t_total
    tempo_find += t_find
    tempo_insere += t_insere
    tempo_remove += t_remove
    tempo_copy += t_copy
    
    best_f = copy.deepcopy(f)
    best_gastos = copy.deepcopy(gastos)
    best_s = copy.deepcopy(s)
    best_total_free = copy.deepcopy(total_free)
    best_total_setup = copy.deepcopy(total_setup)
    best_max_free = copy.deepcopy(max_free)
    best_sondas = copy.deepcopy(sondas)
    
    timer = CPUtimer.CPUTimer()
    timer.reset()
    timer.start()
    
    i = 1
    while(n_iter >= i):
        
        # print ("Iteração: ", i)
        
        i += 1
        
        criterio = np.random.choice(criterios)
        
        alpha = np.random.choice([0.8, 0.85, 0.9, 0.95, 0.99])
        
        beta = np.random.choice([0.1, 0.2, 0.3, 0.4])
        
        # perturbar
        s_temp, gastos_temp, sondas_temp, f_temp, max_free_temp, total_free_temp, total_setup_temp = Perturbar(s, desloc, dados, gastos, sondas, f, max_free, total_free, total_setup, 
                    n_projetos, n_sondas, n_periodos, custo_total, criterio, alpha, beta, debug)
        
        # busca local
        s_temp, gastos_temp, sondas_temp, f_temp, max_free_temp, total_free_temp, total_setup_temp, tempos = BuscaVND(s_temp, gastos_temp, sondas_temp, f_temp, max_free_temp, 
                                                                        total_free_temp, total_setup_temp, dados, 
                                                                        lag, desloc, custo_total, debug, k)
        
        t_preproc, t_total, t_find, t_insere, t_remove, t_copy = tempos
        tempo_preproc += t_preproc
        tempo_busca += t_total
        tempo_find += t_find
        tempo_insere += t_insere
        tempo_remove += t_remove
        tempo_copy += t_copy
        
        # critério de aceitação
        if (f_temp > 0.7*f):
            f = copy.deepcopy(f_temp)
            gastos = copy.deepcopy(gastos_temp)
            s = copy.deepcopy(s_temp)
            total_free = copy.deepcopy(total_free_temp)
            total_setup = copy.deepcopy(total_setup_temp)
            max_free = copy.deepcopy(max_free_temp)
            sondas = copy.deepcopy(sondas_temp)
        
        if (f > best_f):
            best_f = copy.deepcopy(f)
            best_gastos = copy.deepcopy(gastos)
            best_s = copy.deepcopy(s)
            best_total_free = copy.deepcopy(total_free)
            best_total_setup = copy.deepcopy(total_setup)
            best_max_free = copy.deepcopy(max_free)
            best_sondas = copy.deepcopy(sondas)
    
    tempos_return = {"tempo_construcao": tempo_construcao,
                     "tempo_preproc": tempo_preproc,
                     "tempo_busca": tempo_busca,
                     "tempo_find": tempo_find,
                     "tempo_insere": tempo_insere,
                     "tempo_remove": tempo_remove,
                     "tempo_copy": tempo_copy}
    
    check = VerificaRestricoes(best_s, dados, best_f, best_gastos, desloc, best_sondas, 
                               best_max_free, best_total_free, best_total_setup, debug)
    
    tempo_total = timer.get_time(reference = "total", unit = "seconds")
    tempo_medio = timer.get_time(reference = "average", unit = "seconds")
    
    print ("ILS_VND finalizado.")
    
    if check:
        check_str = 'feasible'
    else:
        check_str = 'not feasible'
    
    if print_sol:
        print (check_str)
        print ('fitness: ', best_f)
        print ('gastos: ', best_gastos)
        print ('tempo total de execução (segundos) : ', tempo_total)
        print ('tempo médio de execução (segundos) ', tempo_medio)
        for i in range(n_sondas):
            for node in best_s[i]:
                print ('sonda ', i, ' executa projetos: ', node.data)
    
    return best_f, best_gastos, best_s, tempo_total, tempo_medio, check_str, tempos_return

def ILS_RVND(arquivo, n_iter=100, criterios=None, alpha=0.5, beta=0.5, print_sol=True, debug=False, k=5):
    
    """
    Documentação:
    """
    
    import CPUtimer
    import copy
    import numpy as np
    
    print ("Rodando ILS_RVND...")
    
    if criterios == None:
        criterios = ['lucro/custo', 'lucro/duracao', 'lucro', 'custo', 'duracao', 'janela']
    
    n_projetos, n_sondas, n_periodos, t_init, t_final, delta_t, custo_total, dados, desloc = Read_data(path=arquivo)
    
    lag = n_sondas
    
    tempo_construcao, tempo_preproc, tempo_busca, tempo_find, tempo_insere, tempo_remove, tempo_copy = 0, 0, 0, 0, 0, 0, 0
    
    criterio = np.random.choice(criterios)
    
    f, gastos , s, s_candidatos, sondas, total_free, total_setup, max_free, t_construcao = ConstruirSolucao(dados, 
                                                                           n_projetos, n_sondas, 
                                                                           n_periodos, custo_total, desloc,
                                                                           criterio=criterio, alpha=alpha,
                                                                                             debug=debug)
    
    s, gastos, sondas, f, max_free, total_free, total_setup, tempos = BuscaRVND(s, gastos, sondas, f, max_free, 
                                                                        total_free, total_setup, dados, 
                                                                        lag, desloc, custo_total, debug, k)
    
    tempo_construcao += t_construcao
    t_preproc, t_total, t_find, t_insere, t_remove, t_copy = tempos
    tempo_preproc += t_preproc
    tempo_busca += t_total
    tempo_find += t_find
    tempo_insere += t_insere
    tempo_remove += t_remove
    tempo_copy += t_copy
    
    best_f = copy.deepcopy(f)
    best_gastos = copy.deepcopy(gastos)
    best_s = copy.deepcopy(s)
    best_total_free = copy.deepcopy(total_free)
    best_total_setup = copy.deepcopy(total_setup)
    best_max_free = copy.deepcopy(max_free)
    best_sondas = copy.deepcopy(sondas)
    
    timer = CPUtimer.CPUTimer()
    timer.reset()
    timer.start()
    
    i = 1
    while(n_iter >= i):
        
        # print ("Iterção: ", i)
        
        i += 1
        
        criterio = np.random.choice(criterios)
        
        alpha = np.random.choice([0.8, 0.85, 0.9, 0.95, 0.99])
        
        beta = np.random.choice([0.1, 0.2, 0.3, 0.4])
        
        # perturbar
        s, gastos, sondas, f, max_free, total_free, total_setup = Perturbar(s, desloc, dados, gastos, sondas, f, max_free, total_free, total_setup, 
                    n_projetos, n_sondas, n_periodos, custo_total, criterio, alpha, beta, debug)
        
        # busca local
        s, gastos, sondas, f, max_free, total_free, total_setup, tempos = BuscaRVND(s, gastos, sondas, f, max_free, 
                                                                        total_free, total_setup, dados, 
                                                                        lag, desloc, custo_total, debug, k)
        
        t_preproc, t_total, t_find, t_insere, t_remove, t_copy = tempos
        tempo_preproc += t_preproc
        tempo_busca += t_total
        tempo_find += t_find
        tempo_insere += t_insere
        tempo_remove += t_remove
        tempo_copy += t_copy
        
        # critério de aceitação
        
        
        if (f > best_f):
            best_f = copy.deepcopy(f)
            best_gastos = copy.deepcopy(gastos)
            best_s = copy.deepcopy(s)
            best_total_free = copy.deepcopy(total_free)
            best_total_setup = copy.deepcopy(total_setup)
            best_max_free = copy.deepcopy(max_free)
            best_sondas = copy.deepcopy(sondas)
    
    tempos_return = {"tempo_construcao": tempo_construcao,
                     "tempo_preproc": tempo_preproc,
                     "tempo_busca": tempo_busca,
                     "tempo_find": tempo_find,
                     "tempo_insere": tempo_insere,
                     "tempo_remove": tempo_remove,
                     "tempo_copy": tempo_copy}
    
    check = VerificaRestricoes(best_s, dados, best_f, best_gastos, desloc, best_sondas, 
                               best_max_free, best_total_free, best_total_setup, debug)
    
    tempo_total = timer.get_time(reference = "total", unit = "seconds")
    tempo_medio = timer.get_time(reference = "average", unit = "seconds")
    
    print ("ILS_RVND finalizado.")
    
    if check:
        check_str = 'feasible'
    else:
        check_str = 'not feasible'
    
    if print_sol:
        print (check_str)
        print ('fitness: ', best_f)
        print ('gastos: ', best_gastos)
        print ('tempo total de execução (segundos) : ', tempo_total)
        print ('tempo médio de execução (segundos) ', tempo_medio)
        for i in range(n_sondas):
            for node in best_s[i]:
                print ('sonda ', i, ' executa projetos: ', node.data)
    
    return best_f, best_gastos, best_s, tempo_total, tempo_medio, check_str, tempos_return

def RodarHeuristicaComBuscaLocal(arquivo, criterio='lucro/custo', alpha=0.5, print_sol=True, 
                                 vizinhanca='shift_1x0_interrota', debug=False, k=5):
    
    """
    Documentação:
    
    vizinhancas = ['shift_1x0_interrota', 'shift_2x0_interrota', 
                   'swap_1x1_interrota', 'swap_2x1_interrota', 'swap_2x2_interrota', 
                   'reinsercao_1_intrarota', 'reinsercao_2_intrarota', 
                   'inserir_novo_fo', 'swap_1x1_fo', 'swap_2x1_fo', 'swap_1x2_fo', 'swap_2x2_fo']
    
    """
    
    import CPUtimer
    import copy
    
    n_projetos, n_sondas, n_periodos, t_init, t_final, delta_t, custo_total, dados, desloc = Read_data(path=arquivo)
    
    lag = n_sondas
    
    timer = CPUtimer.CPUTimer()
    timer.reset()
    timer.start()
    
    tempo_construcao, tempo_preproc, tempo_busca, tempo_find, tempo_insere, tempo_remove, tempo_copy = 0, 0, 0, 0, 0, 0, 0
    
    f, gastos, s, s_candidatos, sondas, total_free, total_setup, max_free, t_construcao = ConstruirSolucao(dados, 
                                                                           n_projetos, n_sondas, 
                                                                           n_periodos, custo_total, desloc,
                                                                           criterio=criterio, alpha=alpha,
                                                                                             debug=debug)
    
    if (vizinhanca == "VND"):
        
        # busca VND
        s, gastos, sondas, f, max_free, total_free, total_setup, tempos = BuscaVND(s, gastos, sondas, f, max_free, 
                                                                            total_free, total_setup, dados, 
                                                                            lag, desloc, custo_total, debug, k)
    
    elif (vizinhanca == "RVND"):
        
        # busca R-VND
        s, gastos, sondas, f, max_free, total_free, total_setup, tempos = BuscaRVND(s, gastos, sondas, f, max_free, 
                                                                            total_free, total_setup, dados, 
                                                                            lag, desloc, custo_total, debug, k)
    
    else:
        
        # busca local, dada uma estrutura de vizinhança
        s, gastos, sondas, f, max_free, total_free, total_setup, tempos = BuscaLocal(s, gastos, sondas, f, max_free, 
                                                                             total_free, total_setup, dados, 
                                                                             lag, desloc, custo_total,
                                                                             vizinhanca, debug, k)
    
    
    
    t_preproc, t_total, t_find, t_insere, t_remove, t_copy = tempos
    tempo_preproc += t_preproc
    tempo_busca += t_total
    tempo_find += t_find
    tempo_insere += t_insere
    tempo_remove += t_remove
    tempo_copy += t_copy
    
    tempos_return = {"tempo_construcao": tempo_construcao,
                     "tempo_preproc": tempo_preproc,
                     "tempo_busca": tempo_busca,
                     "tempo_find": tempo_find,
                     "tempo_insere": tempo_insere,
                     "tempo_remove": tempo_remove,
                     "tempo_copy": tempo_copy}
    
    check = VerificaRestricoes(s, dados, f, gastos, desloc, sondas, max_free, total_free, total_setup, debug)
    
    tempo_total = timer.get_time(reference = "total", unit = "seconds")
    tempo_medio = timer.get_time(reference = "average", unit = "seconds")
    
    if check:
        check_str = 'feasible'
    else:
        check_str = 'not feasible'
    
    if print_sol:
        print (check_str)
        print ('fitness: ', f)
        print ('gastos: ', gastos)
        print ('tempo total de execução (segundos) : ', tempo_total)
        print ('tempo médio de execução (segundos) ', tempo_medio)
        for i in range(n_sondas):
            for node in s[i]:
                print ('sonda ', i, ' executa projetos: ', node.data)
    
    return f, gastos, s, tempo_total, tempo_medio, check_str, tempos_return

def RodarHeuristicaSensibilidade(diretorio, criterios=None, alpha=0.5, debug=False):
    
    """
    Documentação:
    """
    
    from os import walk
    import copy
    import pandas as pd
    
    if criterios == None:
        criterios = ['lucro', 'lucro/custo', 'lucro/duracao', 'custo', 'duracao', 'janela']
    
    resultados = {}
    resultados['Instancia'] = []
    resultados['Viabilidade'] = []
    resultados['Criterio guloso'] = []
    resultados['Tempo total (s)'] = []
    resultados['Tempo medio (s)'] = []
    resultados['Valor da função objetivo'] = []
    
    arquivos = _, _, arquivos = next(walk(diretorio))
    arquivos = ["./instancias/" + f for f in arquivos]
    
    for f in arquivos:
        
        print ('processando arquivo: ', f)
        
        for c in criterios:
            
            print ('Utilizando critério ', c)
            
            fitness, gastos, s, t_total, t_medio, feasible = RodarHeuristica(arquivo=f, criterio=c, 
                                                                             alpha=alpha, print_sol=False,
                                                                            debug=debug)
            
            resultados['Instancia'].append(copy.deepcopy(f.split(diretorio)[1]))
            resultados['Viabilidade'].append(copy.deepcopy(feasible))
            resultados['Criterio guloso'].append(copy.deepcopy(c))
            resultados['Tempo total (s)'].append(copy.deepcopy(t_total))
            resultados['Tempo medio (s)'].append(copy.deepcopy(t_medio))
            resultados['Valor da função objetivo'].append(copy.deepcopy(fitness))
    
    df = pd.DataFrame(resultados)
    
    return resultados, df

def RodarVariosArquivos(diretorio, criterios=None, alpha=0.5, debug=False, k=5):
    
    """
    Documentação:
    """
    
    from os import walk
    import copy
    import pandas as pd
    
    resultados = {}
    resultados['Instancia'] = []
    
    resultados['Viabilidade H'] = []
    resultados['Tempo total (s) H'] = []
    resultados['Tempo medio (s) H'] = []
    resultados['Valor da função objetivo H'] = []
    
    resultados['Viabilidade MS'] = []
    resultados['Tempo total (s) MS'] = []
    resultados['Tempo medio (s) MS'] = []
    resultados['Valor da função objetivo MS'] = []
    
    resultados['Viabilidade IG'] = []
    resultados['Tempo total (s) IG'] = []
    resultados['Tempo medio (s) IG'] = []
    resultados['Valor da função objetivo IG'] = []
    
    resultados['Viabilidade GRASP_VND'] = []
    resultados['Tempo total (s) GRASP_VND'] = []
    resultados['Tempo medio (s) GRASP_VND'] = []
    resultados['Valor da função objetivo GRASP_VND'] = []
    
    resultados['Viabilidade GRASP_RVND'] = []
    resultados['Tempo total (s) GRASP_RVND'] = []
    resultados['Tempo medio (s) GRASP_RVND'] = []
    resultados['Valor da função objetivo GRASP_RVND'] = []
    
    resultados['Viabilidade ILS_VND'] = []
    resultados['Tempo total (s) ILS_VND'] = []
    resultados['Tempo medio (s) ILS_VND'] = []
    resultados['Valor da função objetivo ILS_VND'] = []
    
    resultados['Viabilidade ILS_RVND'] = []
    resultados['Tempo total (s) ILS_RVND'] = []
    resultados['Tempo medio (s) ILS_RVND'] = []
    resultados['Valor da função objetivo ILS_RVND'] = []
    
    arquivos = _, _, arquivos = next(walk(diretorio))
    arquivos = [diretorio + "/" + f for f in arquivos]
    
    for f in arquivos:
        
        print ('processando arquivo: ', f)
        
        resultados['Instancia'].append(copy.deepcopy(f.split(diretorio)[1]))
        
        fitness, gastos, s, t_total, t_medio, feasible = RodarHeuristica(arquivo=f, criterio='lucro/custo', 
                                                                             alpha=0.99, print_sol=False,
                                                                             debug=debug)
        
        resultados['Viabilidade H'].append(copy.deepcopy(feasible))
        resultados['Tempo total (s) H'].append(copy.deepcopy(t_total))
        resultados['Tempo medio (s) H'].append(copy.deepcopy(t_medio))
        resultados['Valor da função objetivo H'].append(copy.deepcopy(fitness))
        
        fitness, gastos, s, t_total, t_medio, feasible = MultStart_Heuristic(arquivo=f, n_iter=100,
                                                                             criterios=criterios, 
                                                                             alpha=alpha, print_sol=False,
                                                                             debug=debug)
        
        resultados['Viabilidade MS'].append(copy.deepcopy(feasible))
        resultados['Tempo total (s) MS'].append(copy.deepcopy(t_total))
        resultados['Tempo medio (s) MS'].append(copy.deepcopy(t_medio))
        resultados['Valor da função objetivo MS'].append(copy.deepcopy(fitness))
        
        fitness, gastos, s, t_total, t_medio, feasible = Iterated_Greedy(arquivo=f, n_iter=100, 
                                                                        criterios=criterios, 
                                                                        alpha=alpha, print_sol=False,
                                                                        debug=debug)
        
        resultados['Viabilidade IG'].append(copy.deepcopy(feasible))
        resultados['Tempo total (s) IG'].append(copy.deepcopy(t_total))
        resultados['Tempo medio (s) IG'].append(copy.deepcopy(t_medio))
        resultados['Valor da função objetivo IG'].append(copy.deepcopy(fitness))
        
        fitness, gastos, s, t_total, t_medio, feasible, tempos = GRASP_VND(arquivo=f, n_iter=5, 
                                                                   criterios=criterios, 
                                                                   alpha=alpha, print_sol=False, 
                                                                   debug=debug, k=k)
        
        resultados['Viabilidade GRASP_VND'].append(copy.deepcopy(feasible))
        resultados['Tempo total (s) GRASP_VND'].append(copy.deepcopy(t_total))
        resultados['Tempo medio (s) GRASP_VND'].append(copy.deepcopy(t_medio))
        resultados['Valor da função objetivo GRASP_VND'].append(copy.deepcopy(fitness))

        fitness, gastos, s, t_total, t_medio, feasible, tempos = GRASP_RVND(arquivo=f, n_iter=5, 
                                                                   criterios=criterios, 
                                                                   alpha=alpha, print_sol=False, 
                                                                   debug=debug, k=k)
        
        resultados['Viabilidade GRASP_RVND'].append(copy.deepcopy(feasible))
        resultados['Tempo total (s) GRASP_RVND'].append(copy.deepcopy(t_total))
        resultados['Tempo medio (s) GRASP_RVND'].append(copy.deepcopy(t_medio))
        resultados['Valor da função objetivo GRASP_RVND'].append(copy.deepcopy(fitness))
        
        fitness, gastos, s, t_total, t_medio, feasible, tempos = ILS_VND(arquivo=f, n_iter=5, 
                                                                 criterios=criterios, 
                                                                 alpha=alpha, 
                                                                 beta=0.5, print_sol=False, 
                                                                 debug=debug, k=k)
        
        resultados['Viabilidade ILS_VND'].append(copy.deepcopy(feasible))
        resultados['Tempo total (s) ILS_VND'].append(copy.deepcopy(t_total))
        resultados['Tempo medio (s) ILS_VND'].append(copy.deepcopy(t_medio))
        resultados['Valor da função objetivo ILS_VND'].append(copy.deepcopy(fitness))
        
        fitness, gastos, s, t_total, t_medio, feasible, tempos = ILS_RVND(arquivo=f, n_iter=5, 
                                                                 criterios=criterios, 
                                                                 alpha=alpha, 
                                                                 beta=0.5, print_sol=False, 
                                                                 debug=debug, k=k)
        
        resultados['Viabilidade ILS_RVND'].append(copy.deepcopy(feasible))
        resultados['Tempo total (s) ILS_RVND'].append(copy.deepcopy(t_total))
        resultados['Tempo medio (s) ILS_RVND'].append(copy.deepcopy(t_medio))
        resultados['Valor da função objetivo ILS_RVND'].append(copy.deepcopy(fitness))
        
    
    df = pd.DataFrame(resultados)
    
    return resultados, df

def main():

    import matplotlib.pyplot as plt
    import pandas as pd

    arq = '/home/joaoweissmann/Documents/repos/synthetic_instance_generator/synthetic_instance_generator/1_gerador_instancias_sinteticas/instancias/instancia_10projetos_2sondas_delta_t7.dat'
    
    Read_data(path=arq)

    """
    print ("Rodando heurística de construção, critério=lucro/custo")
    c = 'lucro/custo'
    f, gastos, s, tempo, t_medio, feas = RodarHeuristica(arquivo=arq, criterio=c, alpha=0.99, print_sol=True,
                                                                    debug=False)

    print ("Rodando Multstart Heuristic")

    f, gastos, s, tempo, t_medio, feas = MultStart_Heuristic(arquivo=arq, n_iter=100, criterios=None, 
                                                            alpha=0.80, print_sol=True, debug=False)

    print ("Rodando Iterated Greedy")
    best_f, best_gastos, best_s, tempo_total, tempo_medio, check_str = Iterated_Greedy(arquivo=arq, n_iter=100, 
                                                                                    criterios=None, alpha=0.80, 
                                                                                    print_sol=True, debug=False)
    
    """

    d = "/home/joaoweissmann/Documents/repos/synthetic_instance_generator/synthetic_instance_generator/1_gerador_instancias_sinteticas/instancias"

    rodar_todos = False

    k = 5

    if (rodar_todos):
        resultados, df_resultados = RodarVariosArquivos(diretorio=d, criterios=None, alpha=0.5, debug=False, k=k)
        df_resultados
    
    if (rodar_todos):
        df_resultados.to_csv(path_or_buf='resultados_heuristicas.csv', header=True, index=False, decimal='.')

if (__name__ == "__main__"):
    main()
